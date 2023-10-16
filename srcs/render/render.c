/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 07:21:13 by ele-sage          #+#    #+#             */
/*   Updated: 2023/10/16 11:42:16 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// Calculate the ray for a single pixel
t_ray	get_ray(t_camera *camera, int u, int v, mlx_t *mlx)
{
	t_ray	ray;

	ray.pos = camera->pos;
	ray.dir = vec3_add(camera->dir, vec3_add(vec3_mul(camera->right,
		(2 * camera->half_w * (u + 0.5) / mlx->width - camera->half_w)),
		vec3_mul(camera->up, (2 * camera->half_h * (v + 0.5)
		/ mlx->height - camera->half_h))));
	ray.dir = vec3_norm(ray.dir);
	return (ray);
}

void	add_light(t_objects *objs, t_hit_info *hit_info, t_color *color)
{
	t_ray		light_ray;
	t_hit_info	hits;
	double		dot;

	hits.dist = INFINITY;
	hits.collided = false;
	hits.obj_hit = hit_info->obj_hit;
	light_ray.pos = hit_info->hit.pos;
	light_ray.dir = vec3_norm(vec3_sub(objs->light->pos, hit_info->hit.pos));
	hit(objs, light_ray, &hits);
	dot = vec3_dot(hit_info->hit.dir, light_ray.dir);
	if (dot < 0)
		dot = 0;
	if(hits.collided == false)
	{
		color->r = hit_info->color.r * (objs->light->color.r * dot + objs->amblight->color.r);
		color->g = hit_info->color.g * (objs->light->color.g * dot + objs->amblight->color.g);
		color->b = hit_info->color.b * (objs->light->color.b * dot + objs->amblight->color.b);
	}
	else
	{
		color->r = hit_info->color.r * objs->amblight->color.r;
		color->g = hit_info->color.g * objs->amblight->color.g;
		color->b = hit_info->color.b * objs->amblight->color.b;
	}
	if(color->r > 1)
		color->r = 1;
	if(color->g > 1)
		color->r = 1;
	if(color->b > 1)
		color->r = 1;
}

// void	trace_ray(t_objects *objs, t_ray *ray, t_hit_info *hit_info, t_color *color)
// {
// 	int	bounces = 3;
// 	int	i;

// 	i = 0;
// 	while (i < bounces)
// 	{
// 		hit_info->collided = false;
// 		hit_info->dist = INFINITY;
// 		hit(objs, *ray, hit_info);
// 		if (hit_info->collided)
// 		{
// 			add_light(objs, hit_info, color);
// 			ray->pos = vec3_add(hit_info->hit.pos, vec3_mul(hit_info->hit.dir, 0.0001));
// 			ray->dir = vec3_reflect(ray->dir, hit_info->hit.dir);
// 			ray->dir = vec3_norm(ray->dir);
// 		}
// 		else
// 			return ;
// 		i++;
// 	}
// }

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
	// trace_ray(scene->objs, &ray, &hit_info, color);
	hit(scene->objs, ray, &hit_info);
	if (hit_info.collided)
		add_light(scene->objs, &hit_info, color);
}
