/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   component.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 23:27:35 by ele-sage          #+#    #+#             */
/*   Updated: 2023/10/03 23:29:29 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPONENT_H
# define COMPONENT_H

# include "miniRT.h"

typedef struct	s_color
{
    int			r;
    int			g;
    int			b;
}				t_color;

typedef struct	s_vec3
{
    double		x;
    double		y;
    double		z;
}				t_vec3;

#endif