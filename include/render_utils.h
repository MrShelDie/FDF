/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 10:58:57 by nick              #+#    #+#             */
/*   Updated: 2022/04/10 16:49:30 by nick             ###   ########.fr       */
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

typedef struct s_grad_prm
{
	int		red_a;
	int		green_a;
	int		blue_a;
	int		curr_step;
	float	red_step;
	float	green_step;
	float	blue_step;
}	t_grad_prm;

typedef struct s_draw_prm
{
	int	dx;
	int	dy;
	int	sign_x;
	int	sign_y;
	int	error;
	int	error2;
}	t_draw_prm;

void	init_draw_prm(t_draw_prm *prm, t_point_2d a, t_point_2d b);
void	init_grad_prm(t_grad_prm *prm, t_point_2d a, t_point_2d b);

void	draw_line(t_fdf *fdf, t_image *img, t_point_2d a, t_point_2d b);

void	isometric(t_fdf *fdf);
void	spheric(t_fdf *fdf);

void	transform_point(const t_fdf *fdf, t_point_3d *p);

#endif
