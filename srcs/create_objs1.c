/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_objs1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 01:33:00 by ele-sage          #+#    #+#             */
/*   Updated: 2023/10/04 12:37:27 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static bool init_objects(t_parse *parse, t_objects *object)
{
	char	**components;
    int		i;

    i = 0;
    while (i < parse->nb_line)
    {
		components = ft_split(parse->lines[i], ' ');
		if (!components)
			return (ft_error_free("Malloc error", parse), false);
        if (ft_strncmp(parse->type[i], "s", 2) == 0)
            add_sphere(object, components);
        else if (ft_strncmp(parse->type[i], "p", 2) == 0)
			add_plane(object, components);
		else if (ft_strncmp(parse->type[i], "c", 2) == 0)
			add_cylinder(object, components);
        else if (ft_strncmp(parse->type[i], "C", 2) == 0)
            object->camera = new_camera(components);
        else if (ft_strncmp(parse->type[i], "L", 2) == 0)
            object->light = new_light(components);
        else if (ft_strncmp(parse->type[i], "A", 2) == 0)
            object->amblight = new_amblight(components);
        ft_free_split(components);
        i++;
    }
    return (true);
}

static void fill_null(t_objects *object, t_parse *parse)
{
    int i;

    i = 0;
    while (i < parse->nb_obj[3] + 1)
    {
        object->sphere[i] = NULL;
        i++;
    }
    i = 0;
    while (i < parse->nb_obj[4] + 1)
    {
        object->plane[i] = NULL;
        i++;
    }
    i = 0;
    while (i < parse->nb_obj[5] + 1)
    {
        object->cylinder[i] = NULL;
        i++;
    }
    object->nb_sphere = parse->nb_obj[3];
    object->nb_plane = parse->nb_obj[4];
    object->nb_cylinder = parse->nb_obj[5];
}

t_objects    *new_objects(t_parse *parse)
{
    t_objects	*object;

    object = malloc(sizeof(t_objects));
    if (!object)
        return (NULL);
    object->sphere = malloc(sizeof(t_sphere *) * (parse->nb_obj[3] + 1));
    if (!object->sphere)
        return (free(object), NULL);
    object->plane = malloc(sizeof(t_plane *) * (parse->nb_obj[4] + 1));
    if (!object->plane)
        return (free(object->sphere), free(object), NULL);
    object->cylinder = malloc(sizeof(t_cylinder *) * (parse->nb_obj[5] + 1));
    if (!object->cylinder)
        return (free(object->plane), free(object->sphere), free(object), NULL);
    object->amblight = NULL;
    object->light = NULL;
    object->camera = NULL;
    fill_null(object, parse);
    if (!init_objects(parse, object))
        return (free(object->cylinder), free(object->plane), free(object->sphere), free(object), NULL);
    return (object);
}
