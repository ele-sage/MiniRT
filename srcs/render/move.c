/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 10:54:32 by ele-sage          #+#    #+#             */
/*   Updated: 2023/10/09 16:03:37 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	move(mlx_key_data_t key_data, void *param)
{
	t_scene		*scene;
	t_camera	*camera;

	scene = (t_scene*)param;
	camera = scene->objs->camera;
	if (key_data.key == MLX_KEY_ESCAPE)
	{
		free_scene(scene);
		exit(0);
	}
	if (key_data.key == MLX_KEY_W)
		camera->pos = vec3_add(camera->pos, vec3_mul(camera->dir, 0.1));
	if (key_data.key == MLX_KEY_S)
		camera->pos = vec3_sub(camera->pos, vec3_mul(camera->dir, 0.1));
	if (key_data.key == MLX_KEY_A)
		camera->pos = vec3_add(camera->pos, vec3_mul(camera->right, 0.1));
	if (key_data.key == MLX_KEY_D)
		camera->pos = vec3_sub(camera->pos, vec3_mul(camera->right, 0.1));
	if (key_data.key == MLX_KEY_UP)
		camera->dir = vec3_norm(vec3_add(camera->dir, _vec3(0, 0.1, 0)));
	if (key_data.key == MLX_KEY_DOWN)
		camera->dir = vec3_norm(vec3_sub(camera->dir, _vec3(0, 0.1, 0)));
	if (key_data.key == MLX_KEY_LEFT)
		camera->dir = vec3_norm(vec3_add(camera->dir, _vec3(0.1, 0, 0)));
	if (key_data.key == MLX_KEY_RIGHT)
		camera->dir = vec3_norm(vec3_sub(camera->dir, _vec3(0.1, 0, 0)));
	if (key_data.key == MLX_KEY_W || key_data.key == MLX_KEY_S || key_data.key == MLX_KEY_A || key_data.key == MLX_KEY_D
		|| key_data.key == MLX_KEY_UP || key_data.key == MLX_KEY_DOWN || key_data.key == MLX_KEY_LEFT || key_data.key == MLX_KEY_RIGHT)
		create_thread(scene);
}