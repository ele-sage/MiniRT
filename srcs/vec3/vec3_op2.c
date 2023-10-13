/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_op2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 13:58:09 by ele-sage          #+#    #+#             */
/*   Updated: 2023/10/12 23:35:31 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3	vec3_mul(t_vec3 u, double t)
{
	t_vec3 w;

	w.x = u.x * t;
	w.y = u.y * t;
	w.z = u.z * t;
	return (w);
}

t_vec3	vec3_div(t_vec3 u, double t)
{
	t_vec3 w;

	w.x = u.x / t;
	w.y = u.y / t;
	w.z = u.z / t;
	return (w);
}

t_vec3	vec3_norm(t_vec3 u)
{
	return (vec3_div(u, vec3_length(u)));
}

int32_t	rgba_to_int(t_color *color)
{
	int32_t	r;
	int32_t	g;
	int32_t	b;
	int32_t	a;

	r = (int32_t)(color->r * 255.999);
	g = (int32_t)(color->g * 255.999);
	b = (int32_t)(color->b * 255.999);
	a = 255;
	return (r << 24 | g << 16 | b << 8 | a);
}

t_vec3	vec3_rotate(t_vec3 dir, double angle)
{
	t_vec3	new_dir;

	new_dir.x = dir.x * cos(angle) - dir.y * sin(angle);
	new_dir.y = dir.x * sin(angle) + dir.y * cos(angle);
	new_dir.z = dir.z;
	return (new_dir);
}

void calculateCylinderNormal(t_vec3 v, t_vec3 *n, t_vec3 cylco)
{
	double x = v.x - cylco.x;
	double y = v.y - cylco.y;
	double z = v.z - cylco.z;
    double magnitude = sqrt(x * x + y * y + z * z);

    if (magnitude != 0) {
        n->x = x / magnitude;
        n->y = y / magnitude;
        n->z = z / magnitude;
    } else {
        n->x = 0;
        n->y = 0;
        n->z = 1;
    }
}

t_vec3	vec3_scale(double alpha, t_vec3 a)
{
	return ((t_vec3){alpha * a.x, alpha * a.y, alpha * a.z});
}

t_vec3	vec3_lin_comb(double alpha, t_vec3 a, double beta, t_vec3 b)
{
	return (vec3_add(vec3_scale(alpha, a), vec3_scale(beta, b)));
}

double	vec3_dist(t_vec3 a, t_vec3 b)
{
	return (vec3_length(vec3_sub(a, b)));
}