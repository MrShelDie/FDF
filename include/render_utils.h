/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 10:58:57 by nick              #+#    #+#             */
/*   Updated: 2022/03/14 01:42:31 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_UTILS_H
# define RENDER_UTILS_H

# include "fdf.h"

# define MSF 1
# define LSF 0

typedef struct s_image
{
	void	*img_ptr;
	char	*buff;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}	t_image;

typedef struct s_interp_param
{
	int	color_a;
	int	color_b;
	int	total_step;
	int	current_step;
}	t_interp_param;

void	draw_line(t_fdf *fdf, t_image *img, t_point_2d a, t_point_2d b);
void	isometric(t_fdf *fdf);
void	rotate_point_x(float *x, float *y, float *z, float angle_x);
void	rotate_point_y(float *x, float *y, float *z, float angle_y);
void	rotate_point_z(float *x, float *y, float *z, float angle_z);

#endif
