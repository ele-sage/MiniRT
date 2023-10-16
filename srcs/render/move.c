/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 10:54:32 by ele-sage          #+#    #+#             */
/*   Updated: 2023/10/16 12:15:00 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// Define a function to rotate a vector around the Y-axis
t_vec3 rotate_y(t_vec3 vec, double angle) {
    double cos_a = cos(angle);
    double sin_a = sin(angle);
    t_vec3 result;
    result.x = cos_a * vec.x - sin_a * vec.z;
    result.y = vec.y;
    result.z = sin_a * vec.x + cos_a * vec.z;
    return result;
}

// Define a function to rotate the camera
void rotate_camera(t_camera *camera, double angle) {
    camera->dir = rotate_y(camera->dir, angle);
    camera->right = vec3_cross(camera->dir, (t_vec3){0, 1, 0});
    camera->up = vec3_cross(camera->right, camera->dir);
	camera->dir = vec3_norm(camera->dir);
	camera->right = vec3_norm(camera->right);
	camera->up = vec3_norm(camera->up);
}

void	move(mlx_key_data_t key_data, void *param)
{
	t_scene		*scene;
	t_camera	*camera;
	bool 		changed;

	changed = true;
	scene = (t_scene*)param;
	camera = scene->objs->camera;
	if (key_data.key == MLX_KEY_ESCAPE)
	{
		free_scene(scene);
		exit(0);
	}
	if (key_data.key == MLX_KEY_W)
		camera->pos = vec3_add(camera->pos, vec3_mul(camera->dir, 1));
	else if (key_data.key == MLX_KEY_S)
		camera->pos = vec3_sub(camera->pos, vec3_mul(camera->dir, 1));
	else if  (key_data.key == MLX_KEY_A)
		camera->pos = vec3_sub(camera->pos, vec3_mul(camera->right, 1));
	else if  (key_data.key == MLX_KEY_D)
		camera->pos = vec3_add(camera->pos, vec3_mul(camera->right, 1));
	else if  (key_data.key == MLX_KEY_LEFT)
		rotate_camera(camera, 0.1);
	else if  (key_data.key == MLX_KEY_RIGHT)
		rotate_camera(camera, -0.1);
	else if  (key_data.key == MLX_KEY_UP)
		camera->pos = vec3_add(camera->pos, vec3_mul(camera->up, 1));
	else if  (key_data.key == MLX_KEY_DOWN)
		camera->pos = vec3_sub(camera->pos, vec3_mul(camera->up, 1));
	else
		changed = false;
	if (changed)
		create_thread(scene);
}

void	reseize(int32_t width, int32_t height, void *param)
{
	t_scene		*scene;
	t_camera	*camera;

	scene = (t_scene*)param;
	camera = scene->objs->camera;
	mlx_resize_image(scene->img, width, height);
	camera->up = (t_vec3){0, 1, 0};
	camera->right = vec3_norm(vec3_cross(camera->dir, camera->up));
	camera->aspect_ratio = (double)WIDTH / (double)HEIGHT;
	camera->theta = camera->fov * M_PI / 180;
	camera->half_h = tan(camera->theta / 2);
	camera->half_w = camera->aspect_ratio * camera->half_h;
	create_thread(scene);
}