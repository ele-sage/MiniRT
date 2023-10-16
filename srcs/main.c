/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egervais <egervais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 20:40:31 by ele-sage          #+#    #+#             */
/*   Updated: 2023/10/16 17:05:26 by egervais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	get_objs(t_scene *scene, t_hit_info *hit_info, int pos[2])
{
	t_ray		ray;
	hit_info->collided = false;
	hit_info->dist = INFINITY;

	mlx_get_mouse_pos(scene->mlx, &pos[0], &pos[1]);
	ray = get_ray(scene->objs->camera, pos[0], pos[1], scene->mlx);
	hit(scene->objs, ray, hit_info);
}

void	select_objs(mouse_key_t button, action_t action, modifier_key_t mods, void* param)
{
	t_scene		*scene;
	t_hit_info	hit_info;
	int			pos[2];

	scene = (t_scene*)param;
	mods = 0;
	if (button == MLX_MOUSE_BUTTON_LEFT && action == 0)
	{	
		get_objs(scene, &hit_info, pos);
		if (hit_info.collided)
			scene->selected = hit_info.obj_hit;
	}
	else if(button == MLX_MOUSE_BUTTON_RIGHT && action == 0)
		scene->selected = NULL;
}

int	main(int argc, char **argv)
{
	t_scene	*scene;

	scene = init_scene(argc, argv);
	if (!scene)
		return (1);
	scene->selected = NULL;
	mlx_image_to_window(scene->mlx, scene->img, 0, 0);
	create_thread(scene);
	mlx_resize_hook(scene->mlx, reseize, scene);
	mlx_key_hook(scene->mlx, move, scene);
	mlx_mouse_hook(scene->mlx, select_objs, scene);
	mlx_loop(scene->mlx);
	free_scene(scene);
	return (0);
}
