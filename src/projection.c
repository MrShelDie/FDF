/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 20:48:51 by nick              #+#    #+#             */
/*   Updated: 2022/03/10 01:27:03 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


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
	while (++i < fdf->height)
	{
		j = -1;
		while (++j < fdf->width)
		{
			x = fdf->matrix_3d[i][j].x;
			y = fdf->matrix_3d[i][j].y;
			z = fdf->matrix_3d[i][j].z;
			fdf->matrix_2d[i][j].x = (x * cos(fdf->angle) - y * sin(fdf->angle))
				* ISO_COS_ALPHA + fdf->shift_x;
			fdf->matrix_2d[i][j].y = (x * sin(fdf->angle) + y * cos(fdf->angle))
				* ISO_SIN_BETA + fdf->shift_y - z * fdf->iso_height_scale;
			fdf->matrix_2d[i][j].color = fdf->matrix_3d[i][j].color;
		}
	}
}
