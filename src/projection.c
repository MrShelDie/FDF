/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 20:48:51 by nick              #+#    #+#             */
/*   Updated: 2022/04/03 14:22:27 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "render_utils.h"

#include <math.h>

#include <stdlib.h>

// void	isometric(t_fdf *fdf, float iso_height_scale)
// {
# include <stdio.h>
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

static int	put_color(const t_fdf *fdf, const t_point_3d *p)
{
	float	ratio;
	int		color;

	if (fdf->is_grad_on && fdf->height_max - fdf->height_min != 0)
	{
		ratio = p->z / (fdf->height_max - fdf->height_min);
		color = (RED_HIGH - RED_LOW) * ratio + RED_LOW;
		color <<= 16;
		color |= (int)((BLUE_HIGH - BLUE_LOW) * ratio) + BLUE_LOW;
		return (color);
	}
	return (p->color);
}

void	isometric(t_fdf *fdf)
{
	int			i;
	int			j;
	t_point_3d	p;

	i = -1;
	while (++i < fdf->map_height)
	{
		j = -1;
		while (++j < fdf->map_width)
		{
			p.x = fdf->matrix_3d[i][j].x;
			p.y = fdf->matrix_3d[i][j].y;
			p.z = fdf->matrix_3d[i][j].z;
			rotate_point_local(fdf, &p);
			p.x = (p.x + fdf->shift3d_x) * fdf->zoom;
			p.y = (p.y + fdf->shift3d_y) * fdf->zoom;
			rotate_point_global(fdf, &p);
			fdf->matrix_2d[i][j].x
				= (p.x - p.y) * COS_PI_3 + fdf->shift_x;
			fdf->matrix_2d[i][j].y
				= (p.x + p.y) * SIN_PI_6 + fdf->shift_y - p.z
				* fdf->height_scale;
			fdf->matrix_2d[i][j].color = put_color(fdf, &fdf->matrix_3d[i][j]);
		}
	}
}

void	spheric(t_fdf *fdf)
{
	int			i;
	int			j;
	t_point_3d	p;

	i = -1;
	while (++i < fdf->map_height)
	{
		j = -1;
		while (++j < fdf->map_width)
		{
			p.x = fdf->matrix_3d[i][j].x;
			p.y = fdf->matrix_3d[i][j].y;
			p.z = fdf->matrix_3d[i][j].z;
			rotate_point_local(fdf, &p);
			p.x = (p.x + fdf->shift3d_x) * fdf->zoom;
			p.y = (p.y + fdf->shift3d_y) * fdf->zoom;
			rotate_point_global(fdf, &p);
			p.x = p.x * ((fdf->radius + p.z) / fdf->radius);
			p.y = p.y * ((fdf->radius + p.z) / fdf->radius);
			fdf->matrix_2d[i][j].x = p.x + fdf->shift_x;
			fdf->matrix_2d[i][j].y = p.y + fdf->shift_y;
			fdf->matrix_2d[i][j].color = put_color(fdf, &fdf->matrix_3d[i][j]);
		}
	}
}


			// float R = 350;
			// x = x * ((R + z) / R);
			// y = y * ((R + z) / R);
			// z = sqrt( pow(R + z, 2) - pow(x, 2) - pow(y, 2) );



// if (pow(fdf->radius + p.z, 2) >= pow(p.x * ((fdf->radius + p.z) / fdf->radius), 2) + pow(p.y * ((fdf->radius + p.z) / fdf->radius), 2))
// 			{
// 				p.x = p.x * ((fdf->radius + p.z) / fdf->radius);
// 				p.y = p.y * ((fdf->radius + p.z) / fdf->radius);
// 				p.z = sqrt(pow(fdf->radius + p.z, 2) - pow(p.x, 2) -  pow(p.y, 2));
// 			}
// 			// else
// 			// 	p.z = 0;
// 			fdf->matrix_2d[i][j].x = p.x + fdf->shift_x;
// 			fdf->matrix_2d[i][j].y = p.y + fdf->shift_y; //- p.z * fdf->height_scale;
// 			fdf->matrix_2d[i][j].color = fdf->matrix_3d[i][j].color;