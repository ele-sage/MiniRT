/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 22:13:04 by ele-sage          #+#    #+#             */
/*   Updated: 2023/10/04 13:09:02 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static bool	check_extension(int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc != 2)
		return (ft_error(ERR_FILE), false);
	while (argv[1][i])
		i++;
	if (i < 4)
		return (ft_error(ERR_EXT), false);
	if (argv[1][i - 1] != 't' || argv[1][i - 2] != 'r' || argv[1][i - 3] != '.')
		return (ft_error(ERR_EXT), false);
	return (true);
}

static void	check_objs(t_parse *parse, char **elem)
{
	if (ft_strncmp(elem[0], "A", 2) == 0)
		parse->is_valid = check_ambient(elem, parse);
	else if (ft_strncmp(elem[0], "C", 2) == 0)
		parse->is_valid = check_camera(elem, parse);
	else if (ft_strncmp(elem[0], "L", 2) == 0)
		parse->is_valid = check_light(elem, parse);
	else if (ft_strncmp(elem[0], "sp", 3) == 0)
		parse->is_valid = check_sphere(elem, parse);
	else if (ft_strncmp(elem[0], "cy", 3) == 0)
		parse->is_valid = check_cylinder(elem, parse);
	else if (ft_strncmp(elem[0], "pl", 3) == 0)
		parse->is_valid = check_plane(elem, parse);
	else
		parse->is_valid = false;
}

static bool	check_line(t_parse *parse)
{
	char		**elem;
	int			i;

	i = 0;
	elem = ft_split(parse->line, ' ');
	if (!elem)
		return (false);
	if (ft_splitlen(elem) > 2)
		check_objs(parse, elem);
	else
		parse->is_valid = false;
	ft_free_split(elem);
	if (parse->is_valid)
		return (true);
	return (false);
}

static bool	fill_tab(t_parse *parse)
{
	int	i;

	i = 0;
	parse->line = ft_gnl_join(parse->fd);
	if (!parse->line)
		return (false);
	parse->lines = ft_split(parse->line, '\n');
	free(parse->line);
	if (!parse->lines)
		return (false);
	parse->nb_line = ft_splitlen(parse->lines);
	parse->type = malloc(sizeof(char *) * parse->nb_line + 1);
	if (!parse->type)
		return (false);
	parse->type[parse->nb_line] = NULL;
	while (i < parse->nb_line)
	{
		parse->type[i] = malloc(sizeof(char) * 2);
		if (!parse->type[i])
			return (false);
		parse->type[i][0] = parse->lines[i][0];
		parse->type[i][1] = '\0';
		parse->line = parse->lines[i];
		if (!check_line(parse))
			return (false);
		i++;
	}
	return (true);
}

t_parse	*parsing(int argc, char **argv)
{
	t_parse	*parse;

	if (!check_extension(argc, argv))
		return (NULL);
	parse = malloc(sizeof(t_parse));
	if (!parse)
		return (ft_error(ERR_MALLOC), NULL);
	parse->nb_obj[0] = 0;
	parse->nb_obj[1] = 0;
	parse->nb_obj[2] = 0;
	parse->nb_obj[3] = 0;
	parse->nb_obj[4] = 0;
	parse->nb_obj[5] = 0;
	parse->file = argv[1];
	parse->line = NULL;
	parse->is_valid = true;
	parse->fd = open(parse->file, O_RDONLY);
	if (parse->fd < 0)
		return (ft_error_free(ERR_OPEN, parse));
	if (!fill_tab(parse))
		return (ft_error_free(ERR_READ, parse));
	if (parse->nb_obj[0] != 1 || parse->nb_obj[1] != 1 || parse->nb_obj[2] != 1)
		return (ft_error_free(REQUIRED, parse));
	close(parse->fd);
	return (parse);
}
