/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 12:35:49 by nick              #+#    #+#             */
/*   Updated: 2022/03/07 15:58:05 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "mlx.h"
#include "fdf.h"
#include "render_utils.h"

static void	put_color(t_image *img, int pixel, unsigned int color)
{
	char	*buffer;

	buffer = img->buff;
	if (img->endian == MSF)
	{
		buffer[pixel + 0] = (color >> 24);
		buffer[pixel + 1] = (color >> 16) & 0xFF;
		buffer[pixel + 2] = (color >> 8) & 0xFF;
		buffer[pixel + 1] = (color) & 0xFF;
	}
	else
	{
		buffer[pixel + 0] = (color) & 0xFF;
		buffer[pixel + 1] = (color >> 8) & 0xFF;
		buffer[pixel + 2] = (color >> 16) & 0xFF;
		buffer[pixel + 3] = (color >> 24);
	}
}

static void	put_pixel(t_fdf *fdf, t_image *img, const t_point_2d *point)
{
	int				x;
	int				y;
	int				pixel;
	unsigned int	color;

	x = point->x;
	y = point->y;
	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	if (img->bits_per_pixel != 32)
		color = mlx_get_color_value(fdf->mlx_ptr, point->color);
	else
		color = point->color;
	pixel = (y * img->size_line) + (x * 4);
	put_color(img, pixel, color);
}

void	draw_line(t_fdf *fdf, t_image *img, t_point_2d a, t_point_2d b)
{
	float	dx;
	float	dy;
	int		step;

	dx = abs((int)b.x - (int)a.x);
	dy = abs((int)b.y - (int)a.y);
	if (dx > dy)
		step = dx;
	else
		step = dy;
	dx = dx / step;
	dy = dy / step;
	while (a.x != b.x)
	{
		put_pixel(fdf, img, &a);
		a.x += dx;
		a.y += dy;
	}
}
