/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 20:37:59 by nick              #+#    #+#             */
/*   Updated: 2022/03/14 01:42:08 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "fdf.h"

void	scale_3d(t_fdf *fdf, float scale)
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

void	shift_3d(t_fdf *fdf, int x, int y)
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

void	rotate_point_x(float *x, float *y, float *z, float angle_x)
{
	float	y1;
	float	z1;
	float	cos_angle;
	float	sin_angle;

	cos_angle = cos(angle_x);
	sin_angle = sin(angle_x);
	y1 = *y * cos_angle - *z * sin_angle;
	z1 = *y * sin_angle + *z * cos_angle;
	*y = y1;
	*z = z1;
}

void	rotate_point_y(float *x, float *y, float *z, float angle_y)
{
	float	x1;
	float	z1;
	float	cos_angle;
	float	sin_angle;

	cos_angle = cos(angle_y);
	sin_angle = sin(angle_y);
	x1 = *x * cos_angle + *z * sin_angle;
	z1 = *x * (-sin_angle) + *z * cos_angle;
	*x = x1;
	*z = z1;
}

void	rotate_point_z(float *x, float *y, float *z, float angle_z)
{
	float	x1;
	float	y1;
	float	cos_angle;
	float	sin_angle;

	cos_angle = cos(angle_z);
	sin_angle = sin(angle_z);
	x1 = *x * cos_angle - *y * sin_angle;
	y1 = *x * sin_angle + *y * cos_angle;
	*x = x1;
	*y = y1;
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
