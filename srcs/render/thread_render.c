/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egervais <egervais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 13:52:46 by ele-sage          #+#    #+#             */
/*   Updated: 2023/10/15 20:46:49 by egervais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	*render_thread(void *arg)
{
	t_thread	*data;
	int			u;
	int			v;
	t_color		color;

	data = (t_thread *)arg;
	v = data->thread_id * (data->scene->mlx->height / THREADS);
	while (v < (data->thread_id + 1) * (data->scene->mlx->height / THREADS))
	{
		u = 0;
		while (u < data->scene->mlx->width)
		{
			color = (t_color){0, 0, 100, 255};
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