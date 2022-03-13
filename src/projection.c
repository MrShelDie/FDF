/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 20:48:51 by nick              #+#    #+#             */
/*   Updated: 2022/03/14 01:43:46 by nick             ###   ########.fr       */
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
	float	x;
	float	y;
	float	z;

	i = -1;
	while (++i < fdf->map_height)
	{
		j = -1;
		while (++j < fdf->map_width)
		{
			x = fdf->matrix_3d[i][j].x;
			y = fdf->matrix_3d[i][j].y;
			z = fdf->matrix_3d[i][j].z;
			rotate_point_x(&x, &y, &z, fdf->angle_x);
			rotate_point_y(&x, &y, &z, fdf->angle_y);
			rotate_point_z(&x, &y, &z, fdf->angle_z);
			fdf->matrix_2d[i][j].x = (x - y) * ISO_COS_ALPHA + fdf->shift_x;
			fdf->matrix_2d[i][j].y = (x + y) * ISO_SIN_BETA + fdf->shift_y - z
				* fdf->height_scale;
			fdf->matrix_2d[i][j].color = fdf->matrix_3d[i][j].color;
		}
	}
}




			// float R = 350;
			// x = x * ((R + z) / R);
			// y = y * ((R + z) / R);
			// z = sqrt( pow(R + z, 2) - pow(x, 2) - pow(y, 2) );
