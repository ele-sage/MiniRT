/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 20:40:31 by ele-sage          #+#    #+#             */
/*   Updated: 2023/10/03 21:49:25 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

#define WIDTH 256
#define HEIGHT 256

// Exit the program as failure.
static void ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

// Write MiniRT on the window.
static void write_on_window(mlx_t* mlx)
{
    mlx_put_string(mlx, "MiniRT", 10, 10);
}

int32_t	main(void)
{

	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "MiniRT", true);
	if (!mlx)
		ft_error();

	mlx_image_t* img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		ft_error();

    write_on_window(mlx);

	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}