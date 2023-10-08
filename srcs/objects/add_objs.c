/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_objs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 10:13:42 by ele-sage          #+#    #+#             */
/*   Updated: 2023/10/04 12:30:02 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3 new_vec3(char **components)
{
    t_vec3	vec3;

    vec3.x = ft_atof(components[0]);
    vec3.y = ft_atof(components[1]);
    vec3.z = ft_atof(components[2]);
    return (vec3);
}

t_color new_color(char **components)
{
    t_color	color;

    color.r = ft_atoi(components[0]);
    color.g = ft_atoi(components[1]);
    color.b = ft_atoi(components[2]);
    return (color);
}

void add_sphere(t_objects *object, char **components)
{
    int i;

    i = 0;
    while (object->sphere[i])
        i++;
    object->sphere[i] = new_sphere(components);
}

void add_plane(t_objects *object, char **components)
{
    int i;

    i = 0;
    while (object->plane[i])
        i++;
    object->plane[i] = new_plane(components);
}

void add_cylinder(t_objects *object, char **components)
{
    int i;

    i = 0;
    while (object->cylinder[i])
        i++;
    object->cylinder[i] = new_cylinder(components);
}