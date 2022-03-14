/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_point.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 20:16:16 by nick              #+#    #+#             */
/*   Updated: 2022/03/14 20:57:40 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "fdf.h"
#include "render_utils.h"

static void	rotate_point_x(float angle_x, t_point *p)
{
	float	y1;
	float	z1;
	float	cos_angle;
	float	sin_angle;

	cos_angle = cos(angle_x);
	sin_angle = sin(angle_x);
	y1 = p->y * cos_angle - p->z * sin_angle;
	z1 = p->y * sin_angle + p->z * cos_angle;
	p->y = y1;
	p->z = z1;
}

static void	rotate_point_y(float angle_y, t_point *p)
{
	float	x1;
	float	z1;
	float	cos_angle;
	float	sin_angle;

	cos_angle = cos(angle_y);
	sin_angle = sin(angle_y);
	x1 = p->x * cos_angle + p->z * sin_angle;
	z1 = p->x * (-sin_angle) + p->z * cos_angle;
	p->x = x1;
	p->z = z1;
}

static void	rotate_point_z(float angle_z, t_point *p)
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

void	rotate_point(const t_fdf *prm, t_point *p)
{
	rotate_point_x(prm->angle_x, p);
	rotate_point_x(prm->angle_y, p);
	rotate_point_x(prm->angle_z, p);
}