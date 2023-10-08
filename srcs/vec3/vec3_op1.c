/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_op1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 13:57:07 by ele-sage          #+#    #+#             */
/*   Updated: 2023/10/07 14:02:45 by ele-sage         ###   ########.fr       */
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