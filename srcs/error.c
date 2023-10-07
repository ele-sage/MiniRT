/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 00:42:10 by ele-sage          #+#    #+#             */
/*   Updated: 2023/10/04 03:37:29 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	ft_error(char *str)
{
	ft_putstr_fd("\033[1;31mError\n\033[0m", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	return (false);
}

void	*ft_error_free(t_parse *ptr)
{
	free_parsing(ptr);
	return (NULL);
}