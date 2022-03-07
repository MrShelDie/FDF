/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 20:48:51 by nick              #+#    #+#             */
/*   Updated: 2022/03/08 00:59:06 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


#include <math.h>

void	isometric(t_fdf *fdf, float height_scale)
{
	int	i;
	int	j;
	int	x_3d;
	int	y_3d;
	int	z_3d;

	i = -1;
	while (++i < fdf->height)
	{
		j = -1;
		while (++j < fdf->width)
		{
			x_3d = fdf->matrix_3d[i][j].x;
			y_3d = fdf->matrix_3d[i][j].y;
			z_3d = fdf->matrix_3d[i][j].z;
			fdf->matrix_2d[i][j].x = x_3d - y_3d;
			fdf->matrix_2d[i][j].y = x_3d / 2 + y_3d / 2 - z_3d * height_scale;
			fdf->matrix_2d[i][j].color = fdf->matrix_3d[i][j].color;
		}
	}
}
