/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   component.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 23:27:35 by ele-sage          #+#    #+#             */
/*   Updated: 2023/10/10 18:58:22 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPONENT_H
# define COMPONENT_H

# include "miniRT.h"

typedef struct	s_color
{
	int			r;
	int			g;
	int			b;
	int			a;
}				t_color;

typedef struct	s_vec3
{
	double		x;
	double		y;
	double		z;
}				t_vec3;

typedef struct	s_mat3
{
	union
	{
		double 		m[9];
		t_vec3 		rows[3];
	};
	
}				t_mat3;


typedef struct	s_ray
{
	t_vec3		pos;
	t_vec3		dir;
}				t_ray;

typedef struct	s_hit_info
{
	t_ray		hit;
	t_color		color;
	double		dist;
	int			collided;
}				t_hit_info;

t_vec3		vec3_add(t_vec3 u, t_vec3 v);
t_vec3		vec3_sub(t_vec3 u, t_vec3 v);
double		vec3_dot(t_vec3 u, t_vec3 v);
double		vec3_length(t_vec3 u);
t_vec3		vec3_cross(t_vec3 u, t_vec3 v);
t_vec3		vec3_mul(t_vec3 u, double t);
t_vec3		vec3_div(t_vec3 u, double t);
t_vec3		vec3_norm(t_vec3 u);
t_vec3		vec3_rotate(t_vec3 dir, double angle);
int32_t		rgba_to_int(t_color color);

t_vec3		_vec3(double x, double y, double z);
t_color		_color(int r, int g, int b, int a);
t_ray		_ray(t_vec3 pos, t_vec3 dir);
t_hit_info	_hit_info(t_ray ray, t_color color, double dist, bool hit);
t_hit_info	_hit_info_null(void);

#endif