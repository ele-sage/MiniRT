/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 20:40:31 by ele-sage          #+#    #+#             */
/*   Updated: 2023/10/04 13:06:44 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	main(int argc, char **argv)
{
	t_objects	*objects;
	t_parse		*parse;

	parse = parsing(argc, argv);
	if (!parse)
		return (1);
	objects = new_objects(parse);
	if (!objects)
		return (1);
	free_parsing(parse);
	free_objects(objects);
	return (0);
}