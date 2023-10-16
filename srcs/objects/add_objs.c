/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_objs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egervais <egervais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 10:13:42 by ele-sage          #+#    #+#             */
/*   Updated: 2023/10/16 14:17:57 by egervais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3	new_vec3(char **components)
{
	t_vec3	vec3;

	vec3.x = ft_atof(components[0]);
	vec3.y = ft_atof(components[1]);
	vec3.z = ft_atof(components[2]);
	return (vec3);
}

t_color	new_color(char **components)
{
	t_color	color;

	color.r = ft_atof(components[0]) / 255;
	color.g = ft_atof(components[1]) / 255;
	color.b = ft_atof(components[2]) / 255;
	color.a = 0;
	return (color);
}

void	add_sphere(t_objects *object, char **components)
{
	int	i;

	i = 0;
	while (object->sphere[i])
		i++;
	object->sphere[i] = new_sphere(components);
}

void	add_plane(t_objects *object, char **components)
{
	int	i;

	i = 0;
	while (object->plane[i])
		i++;
	object->plane[i] = new_plane(components);
}

void	add_disk(t_cylinder *cylinder)
{
	t_vec3	origin;

	origin = vec3_add(cylinder->pos,
			vec3_mul(cylinder->dir, cylinder->height / 2));
	cylinder->disk[0].pos = origin;
	cylinder->disk[0].dir = cylinder->dir;
	cylinder->disk[0].radius = cylinder->radius;
	cylinder->disk[0].color = cylinder->color;
	origin = vec3_sub(cylinder->pos,
			vec3_mul(cylinder->dir, cylinder->height / 2));
	cylinder->disk[1].pos = origin;
	cylinder->disk[1].dir = cylinder->dir;
	cylinder->disk[1].radius = cylinder->radius;
	cylinder->disk[1].color = cylinder->color;
}

void	add_cylinder(t_objects *object, char **components)
{
	int	i;

	i = 0;
	while (object->cylinder[i])
		i++;
	object->cylinder[i] = new_cylinder(components);
}
