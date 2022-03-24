/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 20:37:59 by nick              #+#    #+#             */
/*   Updated: 2022/03/24 08:49:00 by nick             ###   ########.fr       */
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
	fdf->radius *= scale;
}

static int	is_extreme_point_in_circle(t_fdf *fdf, t_point *p)
{
	p->x = p->x * ((fdf->radius + p->z) / fdf->radius);
	p->y = p->y * ((fdf->radius + p->z) / fdf->radius);
	if (pow(p->x, 2) + pow(p->y, 2) >= pow(fdf->radius + p->z, 2))
		return (FALSE);
	return (TRUE);
}

static int	check_extreme_point(t_fdf *fdf, int dx, int dy)
{
	t_point	p;

	p.x = fdf->matrix_3d[0][0].x + dx;
	p.y = fdf->matrix_3d[0][0].y + dy;
	p.z = fdf->matrix_3d[0][0].z;
	if (!is_extreme_point_in_circle(fdf, &p))
		return (FALSE);
	p.x = fdf->matrix_3d[0][fdf->map_width - 1].x + dx;
	p.y = fdf->matrix_3d[0][fdf->map_width - 1].y + dy;
	p.z = fdf->matrix_3d[0][fdf->map_width - 1].z;
	if (!is_extreme_point_in_circle(fdf, &p))
		return (FALSE);
	p.x = fdf->matrix_3d[fdf->map_height - 1][0].x + dx;
	p.y = fdf->matrix_3d[fdf->map_height - 1][0].y + dy;
	p.z = fdf->matrix_3d[fdf->map_height - 1][0].z;
	if (!is_extreme_point_in_circle(fdf, &p))
		return (FALSE);
	p.x = fdf->matrix_3d[fdf->map_height - 1][fdf->map_width - 1].x + dx;
	p.y = fdf->matrix_3d[fdf->map_height - 1][fdf->map_width - 1].y + dy;
	p.z = fdf->matrix_3d[fdf->map_height - 1][fdf->map_width - 1].z;
	if (!is_extreme_point_in_circle(fdf, &p))
		return (FALSE);
	return (TRUE);
}

void	shift_map(t_fdf *fdf, int dx, int dy)
{
	int		i;
	int		j;

	if (!check_extreme_point(fdf, dx, dy))
		return ;
	i = -1;
	while (++i < fdf->map_height)
	{
		j = -1;
		while (++j < fdf->map_width)
		{
			fdf->matrix_3d[i][j].x += dx;
			fdf->matrix_3d[i][j].y += dy;
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
// 	while (++i < fdf->map_height)
// 	{
// 		j = -1;
// 		while (++j < fdf->map_width)
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
