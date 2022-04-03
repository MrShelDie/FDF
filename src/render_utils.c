/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 12:35:49 by nick              #+#    #+#             */
/*   Updated: 2022/04/03 15:43:14 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "mlx.h"
#include "fdf.h"
#include "render_utils.h"


#include <limits.h>

static void	put_color(t_image *img, int pixel, int color)
{
	char	*buffer;

	buffer = img->buff;
	if (img->endian == MSF)
	{
		buffer[pixel + 0] = (color >> 24);
		buffer[pixel + 1] = (color >> 16) & 0xFF;
		buffer[pixel + 2] = (color >> 8) & 0xFF;
		buffer[pixel + 3] = (color) & 0xFF;
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
	int	x;
	int	y;
	int	pixel;
	int	color;

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

static void	interp_color(t_grad_prm *prm, t_point_2d *p)
{
	p->color = prm->red_a + prm->red_step * prm->curr_step;
	p->color <<= 16;
	p->color |= (int)(prm->blue_a + prm->blue_step * prm->curr_step);
	prm->curr_step++;
}

static void	init_grad_prm(
	t_grad_prm *prm, int color_a, int color_b, float total_step)
{
	prm->red_a = (color_a >> 16) & 0xff;
	prm->blue_a = color_a & 0xff;
	prm->red_step = ((color_b >> 16 & 0xff) - prm->red_a) / total_step;
	prm->blue_step = ((color_b & 0xff) - prm->blue_a) / total_step;
	prm->curr_step = 0;
}

void	draw_line(t_fdf *fdf, t_image *img, t_point_2d a, t_point_2d b)
{
	float		dx;
	float		dy;
	int			max;
	t_grad_prm	grad_prm;

	if (b.x > 3 * WIN_WIDTH || a.x > 3 * WIN_WIDTH || b.y > 3 * WIN_WIDTH
		|| a.y > 3 * WIN_WIDTH || b.x < -2 * WIN_WIDTH || a.x < -2 * WIN_WIDTH
		|| b.y < -2 * WIN_WIDTH || a.y < -2 * WIN_WIDTH)
		return ;
	dx = b.x - a.x;
	dy = b.y - a.y;
	if (abs((int)dx) > abs((int)dy))
		max = abs((int)dx);
	else
		max = abs((int)dy);
	dx /= max;
	dy /= max;
	init_grad_prm(&grad_prm, a.color, b.color, max);
	while ((int)(b.x - a.x) || (int)(b.y - a.y))
	{
		if (fdf->is_grad_on)
			interp_color(&grad_prm, &a);
		put_pixel(fdf, img, &a);
		a.x += dx;
		a.y += dy;
	}
}
