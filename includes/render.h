/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 07:50:04 by ele-sage          #+#    #+#             */
/*   Updated: 2023/10/09 16:19:00 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "miniRT.h"

t_color		frag(t_scene *scene, int x, int y);
t_ray		get_ray(t_camera *camera, int u, int v, mlx_t *mlx);

void		hit_sphere(t_sphere *sphere, t_ray ray, t_hit_info *hit_info);
void		hit_plane(t_plane *plane, t_ray ray, t_hit_info *hit_info);
void		hit_cylinder(t_cylinder *cylinder, t_ray ray, t_hit_info *hit_info);
void		hit(t_objects *objects, t_ray ray, t_hit_info *hit_info);

#endif