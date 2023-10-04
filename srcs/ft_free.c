/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 01:46:27 by ele-sage          #+#    #+#             */
/*   Updated: 2023/10/04 13:05:11 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	free_parsing(t_parse *parse)
{
	if (parse->lines)
		ft_free_split(parse->lines);
	if (parse->type)
		ft_free_split(parse->type);
	free(parse);
}

void	free_objects(t_objects *object)
{
	int	i;

	i = 0;
	while (i < object->nb_sphere)
	{
		free(object->sphere[i]);
		i++;
	}
	free(object->sphere);
	i = 0;
	while (i < object->nb_plane)
	{
		free(object->plane[i]);
		i++;
	}
	free(object->plane);
	i = 0;
	while (i < object->nb_cylinder)
	{
		free(object->cylinder[i]);
		i++;
	}
	free(object->cylinder);
	free(object->camera);
	free(object->light);
	free(object->amblight);
	free(object);
}