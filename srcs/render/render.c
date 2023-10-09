/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 07:21:13 by ele-sage          #+#    #+#             */
/*   Updated: 2023/10/09 16:32:40 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// Apply ambient light to the color
t_color	apply_ambient(t_color color, t_amblight ambient)
{
	t_color	ambient_color;

	ambient_color.r = color.r * ambient.ratio * ambient.color.r / 255;
	ambient_color.g = color.g * ambient.ratio * ambient.color.g / 255;
	ambient_color.b = color.b * ambient.ratio * ambient.color.b / 255;
	ambient_color.a = color.a;
	return (ambient_color);
}

// Calculate the ray for a single pixel
t_ray	get_ray(t_camera *camera, int u, int v, mlx_t *mlx)
{
	t_ray	ray;
	double	aspect_ratio;
	double	theta;
	double	half_height;
	double	half_width;

	aspect_ratio = (double)mlx->width / (double)mlx->height;
	theta = camera->fov * M_PI / 180;
	half_height = tan(theta / 2);
	half_width = aspect_ratio * half_height;
	ray.pos = camera->pos;
	ray.dir = vec3_norm(vec3_add(vec3_add(vec3_mul(camera->dir, -1),
		vec3_mul(camera->up, half_height * (1 - 2 * (double)v / mlx->height))),
		vec3_mul(camera->right, half_width * (2 * (double)u / mlx->width - 1))));
	return (ray);
}

// Calculate the color of a single pixel
t_color	frag(t_scene *scene, int u, int v)
{
	t_ray		ray;
	t_hit_info	hit_info;

	hit_info.collided = false;
	hit_info.dist = INFINITY;
	ray = get_ray(scene->objs->camera, u, v, scene->mlx);
	hit(scene->objs, ray, &hit_info);
	if (hit_info.collided)
	{
		return (apply_ambient(hit_info.color, *scene->objs->amblight));
	}
	return ((t_color){0, 0, 0, 255});
}
