/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 22:38:09 by ele-sage          #+#    #+#             */
/*   Updated: 2023/10/04 12:34:44 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool    check_ambient(char **elem, t_parse *parse)
{
    if (parse->nb_obj[0] > 0)
        return (ft_error("Ambient light must be declared only once\n"));
    if (ft_splitlen(elem) != 3)
        return (ft_error("Ambient light must have 3 arguments\n"));
    if (!check_range(elem[1], 0.0, 1.0))
        return (ft_error(ERR_RATIO));
    if (!check_color(elem[2]))
        return (ft_error(ERR_COLOR));
    parse->nb_obj[0]++;
    printf("ambient check\n");
    return (true);
}

bool    check_camera(char **elem, t_parse *parse)
{
    if (parse->nb_obj[1] > 0)
        return (ft_error("Camera must be declared only once\n"));
    if (ft_splitlen(elem) != 4)
        return (ft_error("Camera must have 4 arguments\n"));
    if (!check_coordinates(elem[1]))
        return (ft_error(ERR_VEC3));
    if (!check_normal(elem[2]))
        return (ft_error(ERR_NORMAL));
    if (!check_range(elem[3], 0.0, 180.0))
        return (ft_error("Camera FOV must be between 0 and 180\n"));
    parse->nb_obj[1]++;
    printf("camera check\n");
    return (true);
}

bool    check_light(char **elem, t_parse *parse)
{
    if (parse->nb_obj[2] > 0)
        return (ft_error("Light must be declared only once\n"));
    if (ft_splitlen(elem) != 4)
        return (ft_error("Light must have 4 arguments\n"));
    if (!check_coordinates(elem[1]))
        return (ft_error(ERR_VEC3));
    if (!check_range(elem[2], 0.0, 1.0))
        return (ft_error(ERR_RATIO));
    if (!check_color(elem[3]))
        return (ft_error(ERR_COLOR));
    parse->nb_obj[2]++;
    printf("light check\n");
    return (true);
}

bool    check_sphere(char **elem, t_parse *parse)
{
    if (ft_splitlen(elem) != 4)
        return (ft_error("Sphere must have 4 arguments\n"));
    if (!check_coordinates(elem[1]))
        return (ft_error(ERR_VEC3));
    if (!ft_isfloat(elem[2]) && !ft_isint(elem[2]) && ft_atof(elem[2]) <= 0)
        return (ft_error(ERR_LENGTH));
    if (!check_color(elem[3]))
        return (ft_error(ERR_COLOR));
    parse->nb_obj[3]++;
    return (true);
}

bool    check_cylinder(char **elem, t_parse *parse)
{
    if (ft_splitlen(elem) != 6)
        return (ft_error("Cylinder must have 6 arguments\n"));
    if (!check_coordinates(elem[1]))
        return (ft_error(ERR_VEC3));
    if (!check_normal(elem[2]))
        return (ft_error(ERR_NORMAL));
    if (!ft_isfloat(elem[3]) && !ft_isint(elem[3]) && ft_atof(elem[3]) <= 0)
        return (ft_error(ERR_LENGTH));
    if (!ft_isfloat(elem[4]) && !ft_isint(elem[4]) && ft_atof(elem[4]) <= 0)
        return (ft_error(ERR_LENGTH));
    if (!check_color(elem[5]))
        return (ft_error(ERR_COLOR));
    parse->nb_obj[5]++;
    return (true);
}
