/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egervais <egervais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 07:21:13 by ele-sage          #+#    #+#             */
/*   Updated: 2023/10/17 20:20:16 by egervais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// Calculate the ray for a single pixel
t_ray	get_ray(t_camera *camera, int u, int v, mlx_t *mlx)
{
	t_ray	ray;

	ray.pos = camera->pos;
	ray.dir = vec3_add(camera->dir, vec3_add(vec3_mul(camera->right,
					(2 * camera->half_w *(u
							+ 0.5) / mlx->width - camera->half_w)),
				vec3_mul(camera->up, (2 * camera->half_h
						* (v + 0.5) / mlx->height - camera->half_h))));
	ray.dir = vec3_norm(ray.dir);
	return (ray);
}

void	check_max(t_color *color)
{
	if (color->r > 1)
		color->r = 1;
	if (color->g > 1)
		color->g = 1;
	if (color->b > 1)
		color->b = 1;
}

void	adjust_color(t_color *color, t_hit_info *hit_info,
			t_objects *objs, double l)
{
	if (l >= 0)
	{
		color->r = hit_info->color.r * (l * objs->light->color.r
				+ objs->amblight->color.r * objs->amblight->ratio);
		color->g = hit_info->color.g * (l * objs->light->color.g
				+ objs->amblight->color.g * objs->amblight->ratio);
		color->b = hit_info->color.b * (l * objs->light->color.b
				+ objs->amblight->color.b * objs->amblight->ratio);
	}
	else
	{
		color->r = hit_info->color.r * objs->amblight->color.r
			* objs->amblight->ratio;
		color->g = hit_info->color.g * objs->amblight->color.g
			* objs->amblight->ratio;
		color->b = hit_info->color.b * objs->amblight->color.b
			* objs->amblight->ratio;
	}
}

void	add_light(t_objects *objs, t_hit_info *hit_info,
				t_color *color)
{
	t_ray		light_ray;
	t_hit_info	hits;
	double		dot;
	double		at;

	hits.dist = INFINITY;
	hits.collided = false;
	hits.obj_hit = hit_info->obj_hit;
	light_ray.pos = hit_info->hit.pos;
	light_ray.dir = vec3_norm(vec3_sub(objs->light->pos, hit_info->hit.pos));
	hit(objs, light_ray, &hits);
	dot = vec3_dot(hit_info->hit.dir, light_ray.dir);
	at = 1 / pow(vec3_dist(hit_info->hit.pos, objs->light->pos), 0.1);
	if (dot < 0)
		dot = 0;
	if (hits.collided)
		dot = -1;
	else
		dot *= objs->light->ratio * at;
	adjust_color(color, hit_info, objs, dot);
	check_max(color);
}

// Calculate the color of a single pixel
void	draw_pixel(t_scene *scene, int u, int v, t_color *color)
{
	t_ray		ray;
	t_hit_info	hit_info;

	hit_info.color = (t_color){0, 0, 0, 0};
	hit_info.collided = false;
	hit_info.dist = INFINITY;
	hit_info.obj_hit = NULL;
	ray = get_ray(scene->objs->camera, u, v, scene->mlx);
	hit(scene->objs, ray, &hit_info);
	if (hit_info.collided)
		add_light(scene->objs, &hit_info, color);
}
