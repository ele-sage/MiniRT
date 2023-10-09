/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 08:01:30 by ele-sage          #+#    #+#             */
/*   Updated: 2023/10/09 16:17:13 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

typedef struct	s_equation
{
	double	a;
	double	b;
	double	c;
	double	delta;
	double	t1;
	double	t2;
}				t_equation;

void	hit_sphere(t_sphere *sphere, t_ray ray, t_hit_info *hit_info)
{
	t_equation	equation;
	t_vec3		oc;

	oc = vec3_sub(ray.pos, sphere->pos);
	equation.a = vec3_dot(ray.dir, ray.dir);
	equation.b = 2 * vec3_dot(ray.dir, oc);
	equation.c = vec3_dot(oc, oc) - sphere->radius * sphere->radius;
	equation.delta = equation.b * equation.b - 4 * equation.a * equation.c;
	if (equation.delta < 0)
		return ;
	equation.t1 = (-equation.b + sqrt(equation.delta)) / (2 * equation.a);
	equation.t2 = (-equation.b - sqrt(equation.delta)) / (2 * equation.a);
	if (equation.t1 < 0 && equation.t2 < 0)
		return ;
	if (hit_info->dist < equation.t1 && hit_info->dist < equation.t2)
		return ;
	hit_info->dist = get_min(equation.t1, equation.t2);
	hit_info->collided = true;
	hit_info->hit.pos = vec3_add(ray.pos, vec3_mul(ray.dir, hit_info->dist));
	hit_info->hit.dir = vec3_norm(vec3_sub(hit_info->hit.pos, sphere->pos));
	hit_info->color = sphere->color;
}

void	hit_plane(t_plane *plane, t_ray ray, t_hit_info *hit_info)
{
	double		denom;
	t_vec3		p0l0;
	double		t;

	denom = vec3_dot(plane->dir, ray.dir);
	if (fabs(denom) > 0.0001)
	{
		p0l0 = vec3_sub(plane->pos, ray.pos);
		t = vec3_dot(p0l0, plane->dir) / denom;
		if (t > 0 && t < hit_info->dist)
		{
			hit_info->dist = t;
			hit_info->collided = true;
			hit_info->hit.pos = vec3_add(ray.pos, vec3_mul(ray.dir, t));
			hit_info->hit.dir = plane->dir;
			hit_info->color = plane->color;
		}
	}
}

void	hit_cylinder(t_cylinder *cylinder, t_ray ray, t_hit_info *hit_info)
{
	t_equation	equation;
	t_vec3		oc;
	t_vec3		abc;

	oc = vec3_sub(ray.pos, cylinder->pos);
	abc.x = vec3_dot(ray.dir, ray.dir) - pow(vec3_dot(ray.dir, cylinder->dir), 2);
	abc.y = 2 * (vec3_dot(ray.dir, oc) - vec3_dot(ray.dir, cylinder->dir) * vec3_dot(oc, cylinder->dir));
	abc.z = vec3_dot(oc, oc) - pow(vec3_dot(oc, cylinder->dir), 2) - cylinder->radius * cylinder->radius;
	equation.delta = abc.y * abc.y - 4 * abc.x * abc.z;
	if (equation.delta < 0)
		return ;
	equation.t1 = (-abc.y + sqrt(equation.delta)) / (2 * abc.x);
	equation.t2 = (-abc.y - sqrt(equation.delta)) / (2 * abc.x);
	if (equation.t1 < 0 && equation.t2 < 0)
		return ;
	if (hit_info->dist < equation.t1 && hit_info->dist < equation.t2)
		return ;
	hit_info->dist = get_min(equation.t1, equation.t2);
	hit_info->collided = true;
	hit_info->hit.pos = vec3_add(ray.pos, vec3_mul(ray.dir, hit_info->dist));
	hit_info->hit.dir = vec3_norm(vec3_sub(hit_info->hit.pos, cylinder->pos));
	hit_info->color = cylinder->color;
}

void	hit(t_objects *objects, t_ray ray, t_hit_info *hit_info)
{
	int	i;

	i = 0;
	while (i < objects->nb_sphere)
	{
		hit_sphere(objects->sphere[i], ray, hit_info);
		i++;
	}
	i = 0;
	while (i < objects->nb_plane)
	{
		hit_plane(objects->plane[i], ray, hit_info);
		i++;
	}
	i = 0;
	while (i < objects->nb_cylinder)
	{
		hit_cylinder(objects->cylinder[i], ray, hit_info);
		i++;
	}
}