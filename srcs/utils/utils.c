/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 21:22:08 by ele-sage          #+#    #+#             */
/*   Updated: 2023/10/10 22:15:17 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	pseudo_rand(void)
{
	static double	seed = 0;

	if (seed == 0)
		seed = (double)clock();
	seed = fmod((seed * seed), 1);
	return (seed);
}
