/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 08:01:30 by ele-sage          #+#    #+#             */
/*   Updated: 2023/10/12 23:44:34 by ele-sage         ###   ########.fr       */
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
}

void	hit_plane(t_plane *plane, t_ray ray, t_hit_info *hit_info)
{
	t_equation	equation;
	t_vec3		oc;

	oc = vec3_sub(ray.pos, plane->pos);
	equation.a = vec3_dot(ray.dir, plane->dir);
	equation.b = vec3_dot(oc, plane->dir);
	if (equation.a == 0)
		return ;
	equation.t1 = -equation.b / equation.a;
	if (equation.t1 < 0)
		return ;
	if (hit_info->dist < equation.t1)
		return ;
	hit_info->dist = equation.t1;
	hit_info->collided = true;
	hit_info->hit.pos = vec3_add(ray.pos, vec3_mul(ray.dir, hit_info->dist));
	hit_info->hit.dir = plane->dir;
	hit_info->color = plane->color;
}

void intersect_disc(t_disk *disk, t_ray *ray, t_hit_info *hit_info)
{
	double	denominator;
	double	t;
	t_vec3	hit_pos;
	t_vec3	hit_dir;

	denominator = vec3_dot(disk->dir, ray->dir);
	if (fabs(denominator) > 1e-6)
	{
		t = vec3_dot(vec3_sub(disk->pos, ray->pos), disk->dir) / denominator;
		if (vec3_dist(disk->pos,
				vec3_lin_comb(1.0, ray->pos, t, ray->dir)) <= disk->radius)
		{
			hit_info->dist = t;
			hit_info->collided = true;
			hit_pos = vec3_lin_comb(1.0, ray->pos, t, ray->dir);
			hit_dir = vec3_sub(hit_pos, disk->pos);
			hit_dir = vec3_norm(hit_dir);
			hit_info->hit.pos = hit_pos;
			hit_info->hit.dir = hit_dir;
			hit_info->color = disk->color;
		}
	}
}

static void	intersect_tube_quadratic(t_cylinder *cylinder, t_ray *ray, double abc[3])
{
	t_vec3	ray_x_tube;
	t_vec3	dif_x_dir;

	ray_x_tube = vec3_cross(ray->dir, cylinder->dir);
	abc[0] = vec3_dot(ray_x_tube, ray_x_tube);
	dif_x_dir = vec3_cross(vec3_sub(ray->pos, cylinder->pos), cylinder->dir);
	abc[1] = 2.0 * vec3_dot(ray_x_tube, dif_x_dir);
	abc[2] = vec3_dot(dif_x_dir, dif_x_dir) - cylinder->radius * cylinder->radius;
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
	h = vec3_dot(vec3_sub(vec3_lin_comb(
					1.0, ray->pos, t, ray->dir), cylinder->pos), cylinder->dir);
	if (fabs(h) > cylinder->height / 2.0)
	{
		t = (-abc[1] + d) / (2.0 * abc[0]);
		h = vec3_dot(vec3_sub(vec3_lin_comb(
						1.0, ray->pos, t, ray->dir), cylinder->pos), cylinder->dir);
		if (fabs(h) > cylinder->height / 2.0)
			return ;
	}
	hit_info->dist = t;
	hit_info->collided = true;
	hit_info->hit.pos = vec3_add(ray->pos, vec3_mul(ray->dir, hit_info->dist));
	calculateCylinderNormal(hit_info->hit.pos, &hit_info->hit.dir, cylinder->pos);
	hit_info->hit.dir = vec3_norm(hit_info->hit.dir);
	hit_info->color = cylinder->color;
}

void	hit_cylinder(t_cylinder *cylinder, t_ray ray, t_hit_info *hit_info)
{
	t_disk	disk[2];
	t_ray	ray2;

	disk[0].pos = vec3_add(cylinder->pos, vec3_mul(cylinder->dir, cylinder->height / 2));
	disk[0].dir = cylinder->dir;
	disk[0].radius = cylinder->radius;
	disk[0].color = cylinder->color;
	disk[1].pos = vec3_add(cylinder->pos, vec3_mul(cylinder->dir, -cylinder->height / 2));
	disk[1].dir = vec3_mul(cylinder->dir, -1);
	disk[1].radius = cylinder->radius;
	disk[1].color = cylinder->color;
	ray2.pos = ray.pos;
	ray2.dir = vec3_mul(ray.dir, -1);
	intersect_disc(&disk[0], &ray, hit_info);
	intersect_disc(&disk[1], &ray, hit_info);
	intersect_tube(cylinder, &ray, hit_info);
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