/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 20:37:59 by nick              #+#    #+#             */
/*   Updated: 2022/04/02 23:36:54 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <limits.h>

#include "fdf.h"


#include <stdio.h>

void	scale_map(t_fdf *fdf, float scale)
{
	fdf->zoom *= scale;
	fdf->height_scale *= scale;
}

void	shift_map(t_fdf *fdf, int dx, int dy)
{
	fdf->shift3d_x += dx / fdf->zoom;
	fdf->shift3d_y += dy / fdf->zoom;
}

void	increase_map_height(t_fdf *fdf, float value)
{
	fdf->height_scale += value / fdf->height_max;
}

void	rotate_map(t_fdf *fdf, float value)
{
	fdf->angle_z += value;
}
