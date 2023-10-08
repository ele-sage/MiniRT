/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 07:21:13 by ele-sage          #+#    #+#             */
/*   Updated: 2023/10/08 11:02:08 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	hit_sphere(t_sphere *sphere, t_ray ray, double t_min, double t_max)
{
	t_vec3	oc;
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	root;

	oc = vec3_sub(ray.pos, sphere->pos);
	a = vec3_dot(ray.dir, ray.dir);
	b = 2.0 * vec3_dot(oc, ray.dir);
	c = vec3_dot(oc, oc) - sphere->radius * sphere->radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (false);
	root = (-b - sqrt(discriminant)) / (2.0 * a);
	if (root < t_min || t_max < root)
	{
		root = (-b + sqrt(discriminant)) / (2.0 * a);
		if (root < t_min || t_max < root)
			return (false);
	}
	return (true);
}

bool	hit_plane(t_plane *plane, t_ray ray, double t_min, double t_max)
{
	double	denom;
	double	t;
	t_vec3	oc;

	denom = vec3_dot(plane->dir, ray.dir);
	if (fabs(denom) > 0.0001)
	{
		oc = vec3_sub(plane->pos, ray.pos);
		t = vec3_dot(oc, plane->dir) / denom;
		if (t > t_min && t < t_max)
			return (true);
	}
	return (false);
}

bool	hit_cylinder(t_cylinder *cylinder, t_ray ray, double t_min, double t_max)
{
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	root;
	t_vec3	oc;
	t_vec3	oc2;

	oc = vec3_sub(ray.pos, cylinder->pos);
	oc2 = vec3_sub(ray.dir, vec3_mul(cylinder->dir, vec3_dot(ray.dir, cylinder->dir)));
	a = vec3_dot(oc2, oc2);
	b = 2.0 * vec3_dot(oc2, oc);
	c = vec3_dot(oc, oc) - cylinder->radius * cylinder->radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (false);
	root = (-b - sqrt(discriminant)) / (2.0 * a);
	if (root < t_min || t_max < root)
	{
		root = (-b + sqrt(discriminant)) / (2.0 * a);
		if (root < t_min || t_max < root)
			return (false);
	}
	return (true);
}

t_color	hit(t_objects *objs, t_ray ray, double t_min, double t_max)
{
	int		i;

	i = 0;
	while (i < objs->nb_sphere)
	{
		if (hit_sphere(objs->sphere[i], ray, t_min, t_max))
			return (objs->sphere[i]->color);
		i++;
	}
	i = 0;
	while (i < objs->nb_plane)
	{
		if (hit_plane(objs->plane[i], ray, t_min, t_max))
			return (objs->plane[i]->color);
		i++;
	}
	i = 0;
	while (i < objs->nb_cylinder)
	{
		if (hit_cylinder(objs->cylinder[i], ray, t_min, t_max))
			return (objs->cylinder[i]->color);
		i++;
	}
	return (_color(0, 0, 0));
}

t_color	ray_color(t_ray ray, t_scene *scene)
{
	t_color	hit_color;

	hit_color = hit(scene->objs, ray, 0.0, INFINITY);
	if (hit_color.r != 0 || hit_color.g != 0 || hit_color.b != 0)
		return (hit_color);
	return (_color(0, 0, 0));
}

void	render(t_scene *scene)
{
	int		i;
	int		j;
	double	viewport_height;
	double	viewport_width;
	double	focal_length;
	t_camera	*camera;
	t_ray	ray;
	t_color	pixel_color;

	i = 0;
	j = 0;
	viewport_height = 2.0;
	viewport_width = scene->width / scene->height * viewport_height;
	focal_length = 1.0;
	camera = scene->objs->camera;
	while (i < scene->height)
	{
		j = 0;
		while (j < scene->width)
		{
			ray.pos = camera->pos;
			ray.dir = vec3_add(camera->dir, vec3_mul(_vec3((j + 0.5) / scene->width - 0.5, (i + 0.5) / scene->height - 0.5, focal_length), camera->fov));
			pixel_color = ray_color(ray, scene);
			mlx_put_pixel(scene->img, j, i, rgba_to_int(pixel_color));
			j++;
		}
		i++;
	}
}

