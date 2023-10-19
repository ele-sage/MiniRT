/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 13:52:46 by ele-sage          #+#    #+#             */
/*   Updated: 2023/10/19 14:11:43 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static char	*which_object(t_scene *scene)
{
	if (scene->selected == (void *)scene->objs->sphere)
		return ("Sphere");
	if (scene->selected == (void *)scene->objs->plane)
		return ("Plane");
	if (scene->selected == (void *)scene->objs->cylinder)
		return ("Cylinder");
	return ("None");
}

void	display_controls(t_scene *scene)
{
	mlx_put_string(scene->mlx, "Controls:", 10, 10);
	mlx_put_string(scene->mlx, "WASD: Move camera", 10, 30);
	mlx_put_string(scene->mlx, "up/down arrows: Move camera up/down", 10, 50);
	mlx_put_string(scene->mlx, "left/right arrows: Rotate camera", 10, 70);
	mlx_put_string(scene->mlx, "Selected object: ", 10, 170);
	mlx_put_string(scene->mlx, which_object(scene), 10, 190);
}

static void	*render_thread(void *arg)
{
	t_thread	*data;
	int			max_v;
	int			u;
	int			v;
	t_color		color;

	data = (t_thread *)arg;
	v = data->thread_id * (data->scene->mlx->height / THREADS);
	max_v = (data->thread_id + 1) * (data->scene->mlx->height / THREADS);
	if (data->thread_id == THREADS - 1)
		max_v = data->scene->mlx->height;
	while (v < max_v)
	{
		u = 0;
		while (u < data->scene->mlx->width)
		{
			color = (t_color){0.1, 0.1, 0.1, 1};
			draw_pixel(data->scene, u, v, &color);
			mlx_put_pixel(data->scene->img, u, v, rgba_to_int(&color));
			u++;
		}
		v++;
	}
	return (NULL);
}

void	create_thread(t_scene *scene)
{
	int			i;
	pthread_t	threads[THREADS];
	t_thread	data[THREADS];

	i = 0;
	while (i < THREADS)
	{
		data[i].scene = scene;
		data[i].thread_id = i;
		pthread_create(&threads[i], NULL, render_thread, &data[i]);
		i++;
	}
	i = 0;
	while (i < THREADS)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}

void	single_thread(t_scene *scene)
{
	int			u;
	int			v;
	t_color		color;

	v = 0;
	while (v < scene->mlx->height)
	{
		u = 0;
		while (u < scene->mlx->width)
		{
			color = (t_color){0.1, 0.1, 0.1, 1};
			draw_pixel(scene, u, v, &color);
			mlx_put_pixel(scene->img, u, v, rgba_to_int(&color));
			u++;
		}
		v++;
	}
}

void render(t_scene *scene)
{
	if (THREADS == 1)
		single_thread(scene);
	else
		create_thread(scene);
	printf("Selected object: %s\n", which_object(scene));
	display_controls(scene);
}