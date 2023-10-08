/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 01:44:43 by ele-sage          #+#    #+#             */
/*   Updated: 2023/10/08 06:33:00 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FREE_H
# define FT_FREE_H

# include "miniRT.h"

void	free_parsing(t_parse *parse);
void	*free_objects(t_objects *object);
void	*free_before_init(t_parse *parse, t_objects *object);
void    *free_all(t_parse *parse, t_objects *object);
void	free_scene(t_scene *scene);

#endif