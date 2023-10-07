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
	int	i;

	i = 0;
	while (i < parse->nb_line)
	{
		free(parse->lines[i]);
		i++;
	}
	free(parse->lines);
	free(parse);
}

void	free_objects(t_objects *object)
{
	int	i;

	i = 0;
	while (i < object->nb_sphere)
		if (object->sphere[i++])
			free(object->sphere[i - 1]);
	i = 0;
	while (i < object->nb_plane)
		if (object->plane[i++])
			free(object->plane[i - 1]);
	i = 0;
	while (i < object->nb_cylinder)
		if (object->cylinder[i++])
			free(object->cylinder[i - 1]);
	free(object->sphere);
	free(object->plane);
	free(object->cylinder);
	if (object->camera)
		free(object->camera);
	if (object->light)
		free(object->light);
	if (object->amblight)
		free(object->amblight);
	free(object);
}

void	*free_before_init(t_parse *parse, t_objects *object)
{
	if (object->sphere)
		free(object->sphere);
	if (object->plane)
		free(object->plane);
	if (object->cylinder)
		free(object->cylinder);
	if (object->camera)
		free(object->camera);
	if (object->light)
		free(object->light);
	if (object->amblight)
		free(object->amblight);
	free(object);
	free_parsing(parse);
	return (NULL);
}

void	*free_all(t_parse *parse, t_objects *object)
{
	free_parsing(parse);
	free_objects(object);
	return (NULL);
}