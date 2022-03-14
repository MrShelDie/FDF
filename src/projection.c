/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 20:48:51 by nick              #+#    #+#             */
/*   Updated: 2022/03/14 20:58:42 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "render_utils.h"

#include <math.h>

// void	isometric(t_fdf *fdf, float iso_height_scale)
// {
// 	int	i;
// 	int	j;
// 	int	x;
// 	int	y;
// 	int	z;

// 	i = -1;
// 	while (++i < fdf->height)
// 	{
// 		j = -1;
// 		while (++j < fdf->width)
// 		{
// 			x = fdf->matrix_3d[i][j].x;
// 			y = fdf->matrix_3d[i][j].y;
// 			z = fdf->matrix_3d[i][j].z;
// 			fdf->matrix_2d[i][j].x = x - y;
// 			fdf->matrix_2d[i][j].y = x / 2 + y / 2 - z * iso_height_scale;
// 			fdf->matrix_2d[i][j].color = fdf->matrix_3d[i][j].color;
// 		}
// 	}
// }

void	isometric(t_fdf *fdf)
{
	int		i;
	int		j;
	t_point	p;

	i = -1;
	while (++i < fdf->map_height)
	{
		j = -1;
		while (++j < fdf->map_width)
		{
			p.x = fdf->matrix_3d[i][j].x;
			p.y = fdf->matrix_3d[i][j].y;
			p.z = fdf->matrix_3d[i][j].z;
			rotate_point(fdf, &p);
			fdf->matrix_2d[i][j].x
				= (p.x - p.y) * COS_PI_3 + fdf->shift_x;
			fdf->matrix_2d[i][j].y = (p.x + p.y) * SIN_PI_6 + fdf->shift_y - p.z
				* fdf->height_scale;
			fdf->matrix_2d[i][j].color = fdf->matrix_3d[i][j].color;
		}
	}
}




			// float R = 350;
			// x = x * ((R + z) / R);
			// y = y * ((R + z) / R);
			// z = sqrt( pow(R + z, 2) - pow(x, 2) - pow(y, 2) );
