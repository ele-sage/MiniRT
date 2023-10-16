/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egervais <egervais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 08:01:30 by ele-sage          #+#    #+#             */
/*   Updated: 2023/10/16 14:34:44 by egervais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	randomize_hit_dir(t_hit_info *hit_info)
{
	t_vec3	random;
	t_vec3	normal;

	random = _vec3(rand() % 100, rand() % 100, rand() % 100);
	normal = vec3_norm(vec3_cross(random, hit_info->hit.dir));
	hit_info->hit.dir = vec3_norm(vec3_cross(normal, hit_info->hit.dir));
}

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
	hit_info->obj_hit = (void *)sphere;
}

void	hit_plane(t_plane *plane, t_ray ray, t_hit_info *hit_info)
{
	double	t;
	double	denom;
	t_vec3	oc;

	denom = vec3_dot(plane->dir, ray.dir);
	if (fabs(denom) > 1e-6)
	{
		oc = vec3_sub(plane->pos, ray.pos);
		t = vec3_dot(oc, plane->dir) / denom;
		if (t < 0 || hit_info->dist < t)
			return ;
		hit_info->dist = t;
		hit_info->collided = true;
		hit_info->hit.pos = vec3_add(ray.pos,
				vec3_mul(ray.dir, hit_info->dist));
		hit_info->hit.dir = plane->dir;
		if (vec3_dot(plane->dir, ray.dir) > 0)
			hit_info->hit.dir = vec3_mul(hit_info->hit.dir, -1);
		hit_info->color = plane->color;
		hit_info->obj_hit = (void *)plane;
	}
}

void	intersect_disc(t_disk *disk, t_ray *ray, t_hit_info *hit_info)
{
	double	t;
	double	denom;
	t_vec3	oc;
	t_vec3	p;
	t_vec3	v;

	denom = vec3_dot(disk->dir, ray->dir);
	if (fabs(denom) > 1e-6)
	{
		oc = vec3_sub(disk->pos, ray->pos);
		t = vec3_dot(oc, disk->dir) / denom;
		if (t < 0 || hit_info->dist < t)
			return ;
		p = vec3_add(ray->pos, vec3_mul(ray->dir, t));
		v = vec3_sub(p, disk->pos);
		if (vec3_dot(v, v) > disk->radius * disk->radius)
			return ;
		hit_info->dist = t;
		hit_info->collided = true;
		hit_info->hit.pos = p;
		hit_info->hit.dir = disk->dir;
		hit_info->color = disk->color;
		hit_info->obj_hit = (void *)disk;
	}
}

static void	normal_of_tube(t_cylinder *cylinder, t_hit_info *hit_info)
{
	t_vec3	proj;
	t_vec3	oc;

	oc = vec3_sub(hit_info->hit.pos, cylinder->pos);
	proj = vec3_mul(cylinder->dir, vec3_dot(oc, cylinder->dir));
	hit_info->hit.dir = vec3_norm(vec3_sub(oc, proj));
}

static void	intersect_tube_quadratic(t_cylinder *cylinder,
		t_ray *ray, double abc[3])
{
	t_vec3	ray_x_tube;
	t_vec3	dif_x_dir;

	ray_x_tube = vec3_cross(ray->dir, cylinder->dir);
	abc[0] = vec3_dot(ray_x_tube, ray_x_tube);
	dif_x_dir = vec3_cross(vec3_sub(ray->pos, cylinder->pos), cylinder->dir);
	abc[1] = 2.0 * vec3_dot(ray_x_tube, dif_x_dir);
	abc[2] = vec3_dot(dif_x_dir,
			dif_x_dir) - cylinder->radius * cylinder->radius;
}

void	set_values(t_hit_info *hit_info, double t,
		t_ray *ray, t_cylinder *cylinder)
{
	hit_info->dist = t;
	hit_info->collided = true;
	hit_info->hit.pos = vec3_add(ray->pos, vec3_mul(ray->dir, hit_info->dist));
	normal_of_tube(cylinder, hit_info);
	hit_info->hit.dir = vec3_norm(hit_info->hit.dir);
	hit_info->color = cylinder->color;
	hit_info->obj_hit = (void *)cylinder;
}

void	intersect_tube(t_cylinder *cylinder, t_ray *ray, t_hit_info *hit_info)
{
	double	abc[3];
	double	d;
	double	h;
	double	t;

	intersect_tube_quadratic(cylinder, ray, abc);
	d = abc[1] * abc[1] - 4.0 * abc[0] * abc[2];
	if (d < 0 || abc[0] < 1e-6)
		return ;
	d = sqrt(d);
	t = (-abc[1] - d) / (2.0 * abc[0]);
	h = vec3_dot(vec3_sub(vec3_lin_comb(1.0, ray->pos, t,
					ray->dir), cylinder->pos), cylinder->dir);
	if (fabs(h) > cylinder->height / 2.0)
	{
		t = (-abc[1] + d) / (2.0 * abc[0]);
		h = vec3_dot(vec3_sub(vec3_lin_comb(1.0, ray->pos, t,
						ray->dir), cylinder->pos), cylinder->dir);
		if (fabs(h) > cylinder->height / 2.0)
			return ;
	}
	if (t < 0 || hit_info->dist < t)
		return ;
	set_values(hit_info, t, ray, cylinder);
}

void	hit_cylinder(t_cylinder *cylinder, t_ray ray, t_hit_info *hit_info)
{
	intersect_disc(&cylinder->disk[0], &ray, hit_info);
	intersect_disc(&cylinder->disk[1], &ray, hit_info);
	intersect_tube(cylinder, &ray, hit_info);
}

void	hit(t_objects *objects, t_ray ray, t_hit_info *hit_info)
{
	int	i;

	i = 0;
	while (i < objects->nb_sphere)
	{
		if ((t_sphere *)hit_info->obj_hit != objects->sphere[i])
			hit_sphere(objects->sphere[i], ray, hit_info);
		i++;
	}
	i = 0;
	while (i < objects->nb_plane)
	{
		if ((t_plane *)hit_info->obj_hit != objects->plane[i])
			hit_plane(objects->plane[i], ray, hit_info);
		i++;
	}
	i = 0;
	while (i < objects->nb_cylinder)
	{
		if ((t_cylinder *)hit_info->obj_hit != objects->cylinder[i])
			hit_cylinder(objects->cylinder[i], ray, hit_info);
		i++;
	}
}
