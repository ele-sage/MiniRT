/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isfloat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 23:38:26 by ele-sage          #+#    #+#             */
/*   Updated: 2023/10/03 23:39:15 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_isfloat(char *str)
{
    int	i;
    int	dot;

    i = 0;
    dot = 0;
    if (str[i] == '-')
        i++;
    while (str[i])
    {
        if (str[i] == '.')
            dot++;
        else if (!ft_isdigit(str[i]))
            return (0);
        i++;
    }
    if (dot != 1)
        return (0);
    return (1);
}