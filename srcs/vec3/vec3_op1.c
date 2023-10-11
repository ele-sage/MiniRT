/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_op1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 13:57:07 by ele-sage          #+#    #+#             */
/*   Updated: 2023/10/11 16:14:02 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3	vec3_add(t_vec3 u, t_vec3 v)
{
    t_vec3 w;

    w.x = u.x + v.x;
    w.y = u.y + v.y;
    w.z = u.z + v.z;
    return (w);
}

t_vec3	vec3_sub(t_vec3 u, t_vec3 v)
{
    t_vec3 w;

    w.x = u.x - v.x;
    w.y = u.y - v.y;
    w.z = u.z - v.z;
    return (w);
}

double	vec3_dot(t_vec3 u, t_vec3 v)
{
    return (u.x * v.x + u.y * v.y + u.z * v.z);
}

double    vec3_length(t_vec3 u)
{
    return (sqrt(vec3_dot(u, u)));
}

t_vec3  vec3_cross(t_vec3 u, t_vec3 v)
{
    t_vec3 w;

    w.x = u.y * v.z - u.z * v.y;
    w.y = u.z * v.x - u.x * v.z;
    w.z = u.x * v.y - u.y * v.x;
    return (w);
}

t_vec3  _vec3(double x, double y, double z)
{
	t_vec3 w;

	w.x = x;
	w.y = y;
	w.z = z;
	return (w);
}

t_color _color(int r, int g, int b, int a)
{
	t_color color;

	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;
	return (color);
}

t_ray	_ray(t_vec3 pos, t_vec3 dir)
{
	t_ray ray;

	ray.pos = pos;
	ray.dir = dir;
	return (ray);
}

t_vec3	vec3_reflect(t_vec3 v, t_vec3 n)
{
	return (vec3_sub(v, vec3_mul(n, 2 * vec3_dot(v, n))));
}

t_color	mix_color(t_color color1, t_color color2)
{
	t_color color;
	double diviser;

	color.r = color1.r + color2.r;
	color.g = color1.g + color2.g;
	color.b = color1.b + color2.b;
	diviser = color.r + color.g + color.b;
	if (color.r > color.g && color.r > color.b)
	{
		color.g *= 1 - (color.r - 255) / diviser;
		color.b *= 1 - (color.r - 255) / diviser;
		color.r = 255;
	}
	else if (color.g > color.r && color.g > color.b)
	{
		color.r *= 1 - (color.g - 255) / diviser;
		color.b *= 1 - (color.g - 255) / diviser;
		color.g = 255;
	}
	else if (color.b > color.r && color.b > color.g)
	{
		color.r *= 1 - (color.b - 255) / diviser;
		color.g *= 1 - (color.b - 255) / diviser;
		color.b = 255;
	}
	return (color);
}