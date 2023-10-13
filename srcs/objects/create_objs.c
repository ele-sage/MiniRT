/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_objs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 01:33:00 by ele-sage          #+#    #+#             */
/*   Updated: 2023/10/12 19:43:35 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_sphere *new_sphere(char **components)
{
    t_sphere	*sphere;
    char        **split;
    
    sphere = malloc(sizeof(t_sphere));
    if (!sphere)
        return (NULL);
    split = ft_split(components[1], ',');
    if (!split)
        return (free(sphere), NULL);
    sphere->pos = new_vec3(split);
    ft_free_split(split);
    sphere->radius = ft_atof(components[2])/2;
    split = ft_split(components[3], ',');
    if (!split)
        return (free(sphere), NULL);
    sphere->color = new_color(split);
    ft_free_split(split);
    return (sphere);
}

t_plane *new_plane(char **components)
{
    t_plane	*plane;
    char    **split;

    plane = malloc(sizeof(t_plane));
    if (!plane)
        return (NULL);
    split = ft_split(components[1], ',');
    if (!split)
        return (free(plane), NULL);
    plane->pos = new_vec3(split);
    ft_free_split(split);
    split = ft_split(components[2], ',');
    if (!split)
        return (free(plane), NULL);
    plane->dir = new_vec3(split);
    ft_free_split(split);
    split = ft_split(components[3], ',');
    if (!split)
        return (free(plane), NULL);
    plane->color = new_color(split);
    ft_free_split(split);
    return (plane);
}

t_cylinder *new_cylinder(char **components)
{
    t_cylinder	*cylinder;
    char        **split;

    cylinder = malloc(sizeof(t_cylinder));
    if (!cylinder)
        return (NULL);
    split = ft_split(components[1], ',');
    if (!split)
        return (free(cylinder), NULL);
    cylinder->pos = new_vec3(split);
    ft_free_split(split);
    split = ft_split(components[2], ',');
    if (!split)
        return (free(cylinder), NULL);
    cylinder->dir = new_vec3(split);
    ft_free_split(split);
    cylinder->radius = ft_atof(components[3])/2;
    cylinder->height = ft_atof(components[4]);
    split = ft_split(components[5], ',');
    if (!split)
        return (free(cylinder), NULL);
    cylinder->color = new_color(split);
    ft_free_split(split);
    return (cylinder);
}

t_amblight *new_amblight(char **components)
{
    t_amblight	*amblight;
    char        **split;

    amblight = malloc(sizeof(t_amblight));
    if (!amblight)
        return (NULL);
    amblight->ratio = ft_atof(components[1]);
    split = ft_split(components[2], ',');
    if (!split)
        return (free(amblight), NULL);
    amblight->color = new_color(split);
    ft_free_split(split);
    return (amblight);
}

t_light *new_light(char **components)
{
    t_light	*light;
    char    **split;

    light = malloc(sizeof(t_light));
    if (!light)
        return (NULL);
    split = ft_split(components[1], ',');
    if (!split)
        return (free(light), NULL);
    light->pos = new_vec3(split);
    ft_free_split(split);
    light->ratio = ft_atof(components[2]);
    split = ft_split(components[3], ',');
    if (!split)
        return (free(light), NULL);
    light->color = new_color(split);
    ft_free_split(split);
	light->color.r *= light->ratio;
	light->color.g *= light->ratio;
	light->color.b *= light->ratio;
    return (light);
}

t_camera *new_camera(char **components)
{
    t_camera	*camera;
    char        **split;

    camera = malloc(sizeof(t_camera));
    if (!camera)
        return (NULL);
    split = ft_split(components[1], ',');
    if (!split)
        return (free(camera), NULL);
    camera->pos = new_vec3(split);
    ft_free_split(split);
    split = ft_split(components[2], ',');
    if (!split)
        return (free(camera), NULL);
    camera->dir = new_vec3(split);
    ft_free_split(split);
    camera->fov = ft_atof(components[3]);
	camera->up = (t_vec3){0, 1, 0};
	camera->right = vec3_norm(vec3_cross(camera->dir, camera->up));
	camera->aspect_ratio = (double)WIDTH / (double)HEIGHT;
	camera->theta = camera->fov * M_PI / 180;
	camera->half_h = tan(camera->theta / 2);
	camera->half_w = camera->aspect_ratio * camera->half_h;
    return (camera);
}