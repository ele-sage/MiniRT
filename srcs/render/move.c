/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egervais <egervais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 10:54:32 by ele-sage          #+#    #+#             */
/*   Updated: 2023/10/16 17:35:42 by egervais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// Define a function to rotate a vector around the Y-axis
t_vec3	rotate_y(t_vec3 vec, double angle)
{
	double	cos_a;
	double	sin_a;
	t_vec3	result;

	cos_a = cos(angle);
	sin_a = sin(angle);
	result.x = cos_a * vec.x - sin_a * vec.z;
	result.y = vec.y;
	result.z = sin_a * vec.x + cos_a * vec.z;
	return (result);
}

// Define a function to rotate the camera
void	rotate_camera(t_camera *camera, double angle)
{
	camera->dir = rotate_y(camera->dir, angle);
	camera->right = vec3_cross(camera->dir, (t_vec3){0, 1, 0});
	camera->up = vec3_cross(camera->right, camera->dir);
	camera->dir = vec3_norm(camera->dir);
	camera->right = vec3_norm(camera->right);
	camera->up = vec3_norm(camera->up);
}

int	move2(keys_t key, t_camera *camera)
{
	if (key == MLX_KEY_W)
		camera->pos = vec3_add(camera->pos, vec3_mul(camera->dir, 1));
	else if (key == MLX_KEY_S)
		camera->pos = vec3_sub(camera->pos, vec3_mul(camera->dir, 1));
	else if (key == MLX_KEY_A)
		camera->pos = vec3_sub(camera->pos, vec3_mul(camera->right, 1));
	else if (key == MLX_KEY_D)
		camera->pos = vec3_add(camera->pos, vec3_mul(camera->right, 1));
	else
		return (1);
	return (0);
}

void	add(t_objects *objects, void *hit)
{
	int i = 0;
	while (i < objects->nb_sphere)
	{
		if ((t_sphere *)hit == objects->sphere[i])
			objects->sphere[i]->radius += 0.1;
		i++;
	}
	i = 0;
	while (i < objects->nb_cylinder)
	{
		if ((t_cylinder *)hit == objects->cylinder[i])
		{
			objects->cylinder[i]->disk[1].radius += 0.1;
			objects->cylinder[i]->disk[0].radius += 0.1;
			objects->cylinder[i]->radius += 0.1;
		}
		i++;
	}
}
void	sub(t_objects *objects, void *hit)
{
	int i = 0;
	while (i < objects->nb_sphere)
	{
		if ((t_sphere *)hit == objects->sphere[i])
			if(objects->sphere[i]->radius - 0.1 > 0)
				objects->sphere[i]->radius -= 0.1;
		i++;
	}
	i = 0;
	while (i < objects->nb_cylinder)
	{
		if ((t_cylinder *)hit == objects->cylinder[i])
			if(objects->cylinder[i]->radius - 0.1 > 0)
			{
				objects->cylinder[i]->disk[1].radius -= 0.1;
				objects->cylinder[i]->disk[0].radius -= 0.1;
				objects->cylinder[i]->radius -= 0.1;
			}
		i++;
	}
}
void new_dir(t_vec3 *co)
{
	if(co->x)
	{
		co->x = 0;
		co->y = 1;
	}
	else if (co->y)
	{
		co->y = 0;
		co->z = 1;
	}
	else
	{
		co->z = 0;
		co->x = 1;
	}
}
void	rot(t_objects *objects, void *hit)
{
	int i = 0;
	while (i < objects->nb_plane)
	{
		if ((t_plane *)hit == objects->plane[i])
			new_dir(&objects->plane[i]->dir);
		i++;
	}
	i = 0;
	while (i < objects->nb_cylinder)
	{
		if ((t_cylinder *)hit == objects->cylinder[i])
		{
			new_dir(&objects->cylinder[i]->dir);
			add_disk(objects->cylinder[i]);
		}
		i++;
	}
}
void	front(t_objects *objects, void *hit)
{
	int i = 0;
	while (i < objects->nb_plane)
	{
		if ((t_plane *)hit == objects->plane[i])
			objects->plane[i]->pos.z += 0.1;
		i++;
	}
	i = 0;
	while (i < objects->nb_cylinder)
	{
		if ((t_cylinder *)hit == objects->cylinder[i])
		{
			objects->cylinder[i]->disk[1].pos.z += 0.1;
			objects->cylinder[i]->disk[0].pos.z += 0.1;
			objects->cylinder[i]->pos.z += 0.1;
		}
		i++;
	}
	i = 0;
	while (i < objects->nb_sphere)
	{
		if ((t_sphere *)hit == objects->sphere[i])
			objects->sphere[i]->pos.z += 0.1;
		i++;
	}
}
void	back(t_objects *objects, void *hit)
{
	int i = 0;
	while (i < objects->nb_plane)
	{
		if ((t_plane *)hit == objects->plane[i])
			objects->plane[i]->pos.z -= 0.1;
		i++;
	}
	i = 0;
	while (i < objects->nb_cylinder)
	{
		if ((t_cylinder *)hit == objects->cylinder[i])
		{
			objects->cylinder[i]->disk[1].pos.z -= 0.1;
			objects->cylinder[i]->disk[0].pos.z -= 0.1;
			objects->cylinder[i]->pos.z -= 0.1;
		}
		i++;
	}
	i = 0;
	while (i < objects->nb_sphere)
	{
		if ((t_sphere *)hit == objects->sphere[i])
			objects->sphere[i]->pos.z -= 0.1;
		i++;
	}
}
void	right(t_objects *objects, void *hit)
{
	int i = 0;
	while (i < objects->nb_plane)
	{
		if ((t_plane *)hit == objects->plane[i])
			objects->plane[i]->pos.x += 0.1;
		i++;
	}
	i = 0;
	while (i < objects->nb_cylinder)
	{
		if ((t_cylinder *)hit == objects->cylinder[i])
		{
			objects->cylinder[i]->disk[1].pos.x += 0.1;
			objects->cylinder[i]->disk[0].pos.x += 0.1;
			objects->cylinder[i]->pos.x += 0.1;
		}
		i++;
	}
	i = 0;
	while (i < objects->nb_sphere)
	{
		if ((t_sphere *)hit == objects->sphere[i])
			objects->sphere[i]->pos.x += 0.1;
		i++;
	}
}
void	left(t_objects *objects, void *hit)
{
	int i = 0;
	while (i < objects->nb_plane)
	{
		if ((t_plane *)hit == objects->plane[i])
			objects->plane[i]->pos.x -= 0.1;
		i++;
	}
	i = 0;
	while (i < objects->nb_cylinder)
	{
		if ((t_cylinder *)hit == objects->cylinder[i])
		{
			objects->cylinder[i]->disk[1].pos.x -= 0.1;
			objects->cylinder[i]->disk[0].pos.x -= 0.1;
			objects->cylinder[i]->pos.x -= 0.1;
		}
		i++;
	}
	i = 0;
	while (i < objects->nb_sphere)
	{
		if ((t_sphere *)hit == objects->sphere[i])
			objects->sphere[i]->pos.x -= 0.1;
		i++;
	}
}
void	up(t_objects *objects, void *hit)
{
	int i = 0;
	while (i < objects->nb_plane)
	{
		if ((t_plane *)hit == objects->plane[i])
			objects->plane[i]->pos.y += 0.1;
		i++;
	}
	i = 0;
	while (i < objects->nb_cylinder)
	{
		if ((t_cylinder *)hit == objects->cylinder[i])
		{
			objects->cylinder[i]->disk[1].pos.y += 0.1;
			objects->cylinder[i]->disk[0].pos.y += 0.1;
			objects->cylinder[i]->pos.y += 0.1;
		}
		i++;
	}
	i = 0;
	while (i < objects->nb_sphere)
	{
		if ((t_sphere *)hit == objects->sphere[i])
			objects->sphere[i]->pos.y += 0.1;
		i++;
	}
}
void	down(t_objects *objects, void *hit)
{
	int i = 0;
	while (i < objects->nb_plane)
	{
		if ((t_plane *)hit == objects->plane[i])
			objects->plane[i]->pos.y -= 0.1;
		i++;
	}
	i = 0;
	while (i < objects->nb_cylinder)
	{
		if ((t_cylinder *)hit == objects->cylinder[i])
		{
			objects->cylinder[i]->disk[1].pos.y -= 0.1;
			objects->cylinder[i]->disk[0].pos.y -= 0.1;
			objects->cylinder[i]->pos.y -= 0.1;
		}
		i++;
	}
	i = 0;
	while (i < objects->nb_sphere)
	{
		if ((t_sphere *)hit == objects->sphere[i])
			objects->sphere[i]->pos.y -= 0.1;
		i++;
	}
}
void	move(mlx_key_data_t key_data, void *param)
{
	t_scene		*scene;
	t_camera	*camera;
	bool		changed;

	changed = true;
	scene = (t_scene *)param;
	camera = scene->objs->camera;
	if (key_data.key == MLX_KEY_ESCAPE)
		free_scene(scene);
	if (key_data.key == MLX_KEY_LEFT)
		rotate_camera(camera, 0.1);
	else if (key_data.key == MLX_KEY_RIGHT)
		rotate_camera(camera, -0.1);
	else if (key_data.key == MLX_KEY_UP)
		camera->pos = vec3_add(camera->pos, vec3_mul(camera->up, 1));
	else if (key_data.key == MLX_KEY_DOWN)
		camera->pos = vec3_sub(camera->pos, vec3_mul(camera->up, 1));
	else if (key_data.key == MLX_KEY_KP_ADD && scene->selected)
		add(scene->objs, scene->selected);
	else if (key_data.key == MLX_KEY_KP_SUBTRACT && scene->selected)
		sub(scene->objs, scene->selected);
	else if (key_data.key == MLX_KEY_R && scene->selected)
		rot(scene->objs, scene->selected);
	else if (key_data.key == MLX_KEY_KP_6 && scene->selected)
		right(scene->objs, scene->selected);
	else if (key_data.key == MLX_KEY_KP_4 && scene->selected)
		left(scene->objs, scene->selected);
	else if (key_data.key == MLX_KEY_KP_8 && scene->selected)
		up(scene->objs, scene->selected);
	else if (key_data.key == MLX_KEY_KP_2 && scene->selected)
		down(scene->objs, scene->selected);
	else if (key_data.key == MLX_KEY_KP_7 && scene->selected)
		front(scene->objs, scene->selected);
	else if (key_data.key == MLX_KEY_KP_9 && scene->selected)
		back(scene->objs, scene->selected);
	else
		if (move2(key_data.key, camera))
			changed = false;
	if (changed)
		create_thread(scene);
}

void	render(t_scene *scene)
{
	int		u;
	int		v;
	t_color	color;

	u = 0;
	while (u < scene->mlx->width)
	{
		v = 0;
		while (v < scene->mlx->height)
		{
			color = (t_color){0, 0, 100, 255};
			draw_pixel(scene, u, v, &color);
			mlx_put_pixel(scene->img, u, v, rgba_to_int(&color));
			v++;
		}
		u++;
	}
}

void	reseize(int32_t width, int32_t height, void *param)
{
	t_scene		*scene;
	t_camera	*camera;

	scene = (t_scene *)param;
	camera = scene->objs->camera;
	camera->aspect_ratio = width / height;
	camera->half_h = camera->half_w * height / width;
	scene->mlx->width = width;
	scene->mlx->height = height;
	mlx_resize_image(scene->img, width, height);
	create_thread(scene);
}
