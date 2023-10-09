/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 06:16:30 by ele-sage          #+#    #+#             */
/*   Updated: 2023/10/09 13:34:10 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static bool	init_mlx(t_scene *scene)
{
	mlx_t		*mlx;
	mlx_image_t	*img;

	scene->width = 1920;
	scene->height = 1080;
	mlx = mlx_init(scene->width, scene->height, "miniRT", true);
	if (!mlx)
		return (false);
	img = mlx_new_image(mlx, scene->width, scene->height);
	if (!img)
	{
		mlx_terminate(mlx);
		return (false);
	}
	scene->mlx = mlx;
	scene->img = img;
	return (true);
}

t_scene	*init_scene(int argc, char **argv)
{
	t_scene		*scene;
	t_parse		*parse;
	t_objects	*object;

	if (argc < 2)
		return (NULL);
	parse = parsing(argc, argv);
	if (!parse)
		return (NULL);
	object = new_objects(parse);
	if (!object)
		return (NULL);
	scene = malloc(sizeof(t_scene));
	if (!scene)
		return (free_objects(object));
	if (!init_mlx(scene))
		return (free(scene), free_objects(object));
	scene->objs = object;
	return (scene);
}