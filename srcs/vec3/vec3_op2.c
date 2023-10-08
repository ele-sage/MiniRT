/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_op2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 13:58:09 by ele-sage          #+#    #+#             */
/*   Updated: 2023/10/08 09:53:32 by ele-sage         ###   ########.fr       */
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

t_vec3	vec3_unit(t_vec3 u)
{
	return (vec3_div(u, vec3_length(u)));
}

int32_t	rgba_to_int(t_color color)
{
	int32_t	rgb;

	rgb = 255;
	return (rgb | (color.r << 24) | (color.g << 16) | color.b << 8);
}