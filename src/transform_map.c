/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 20:37:59 by nick              #+#    #+#             */
/*   Updated: 2022/03/15 09:55:20 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "fdf.h"

void	scale_map(t_fdf *fdf, float scale)
{
	int	i;
	int	j;

	i = -1;
	while (++i < fdf->map_height)
	{
		j = -1;
		while (++j < fdf->map_width)
		{
			fdf->matrix_3d[i][j].x *= scale;
			fdf->matrix_3d[i][j].y *= scale;
			fdf->matrix_3d[i][j].z *= scale;
		}
	}
}

void	shift_map(t_fdf *fdf, int x, int y)
{
	int	i;
	int	j;

	i = -1;
	while (++i < fdf->map_height)
	{
		j = -1;
		while (++j < fdf->map_width)
		{
			fdf->matrix_3d[i][j].x += x;
			fdf->matrix_3d[i][j].y += y;
		}
	}
}

// void	rotate_z_3d(t_fdf *fdf, float angle)
// {
// 	float	cos_angle;
// 	float	sin_angle;
// 	int		i;
// 	int		j;

// 	cos_angle = cos(angle);
// 	sin_angle = sin(angle);
// 	i = -1;
// 	while (++i < fdf->height)
// 	{
// 		j = -1;
// 		while (++j < fdf->width)
// 		{
// 			fdf->matrix_3d[i][j].x = fdf->matrix_3d[i][j].x * cos_angle
// 				- fdf->matrix_3d[i][j].y * sin_angle;
// 			fdf->matrix_3d[i][j].y = fdf->matrix_3d[i][j].x * sin_angle
// 				+ fdf->matrix_3d[i][j].y * cos_angle;
// 		}
// 	}
// }

// void	shift_2d(t_fdf *fdf, int x, int y)
// {
// 	int	i;
// 	int	j;

// 	i = -1;
// 	while (++i < fdf->height)
// 	{
// 		j = -1;
// 		while (++j < fdf->width)
// 		{
// 			fdf->matrix_2d[i][j].x += x;
// 			fdf->matrix_2d[i][j].y += y;
// 		}
// 	}
// }
