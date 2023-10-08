/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 20:40:54 by ele-sage          #+#    #+#             */
/*   Updated: 2023/10/08 06:19:31 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>
# include "../libft/include/libft.h"
# include "../mlx/include/MLX42/MLX42.h"

typedef struct	s_scene t_scene;

# include "parse.h"
# include "component.h"
# include "error.h"
# include "object.h"
# include "ft_free.h"

typedef struct	s_scene
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_objects		*objs;
	uint32_t		width;
	uint32_t		height;
};

# endif