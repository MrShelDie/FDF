/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_point.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 20:16:16 by nick              #+#    #+#             */
/*   Updated: 2022/04/10 16:49:21 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "fdf.h"

static void	rotate_point_z(float angle_z, t_point_3d *p)
{
	float	x1;
	float	y1;
	float	cos_angle;
	float	sin_angle;

	cos_angle = cos(angle_z);
	sin_angle = sin(angle_z);
	x1 = p->x * cos_angle - p->y * sin_angle;
	y1 = p->x * sin_angle + p->y * cos_angle;
	p->x = x1;
	p->y = y1;
}

void	transform_point(const t_fdf *fdf, t_point_3d *p)
{
	p->x += fdf->shift3d_x;
	p->y += fdf->shift3d_y;
	rotate_point_z(fdf->angle_z, p);
	p->x *= fdf->zoom;
	p->y *= fdf->zoom;
}
