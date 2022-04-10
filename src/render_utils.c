/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 12:35:49 by nick              #+#    #+#             */
/*   Updated: 2022/04/10 16:41:06 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "mlx.h"
#include "fdf.h"
#include "render_utils.h"

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

static int	interp_color(t_grad_prm *prm)
{
	int	color;

	color = prm->red_a + prm->red_step * prm->curr_step;
	color <<= 8;
	color |= (int)(prm->green_a + prm->green_step * prm->curr_step);
	color <<= 8;
	color |= (int)(prm->blue_a + prm->blue_step * prm->curr_step);
	prm->curr_step++;
	return (color);
}

static void	put_pixel(
	t_fdf *fdf, t_image *img, t_point_2d *point, t_grad_prm *grad_prm)
{
	int	x;
	int	y;
	int	pixel;
	int	color;

	if (fdf->is_grad_on)
		point->color = interp_color(grad_prm);
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
	t_draw_prm	draw_prm;
	t_grad_prm	grad_prm;

	if (b.x > 3 * WIN_WIDTH || a.x > 3 * WIN_WIDTH || b.y > 3 * WIN_WIDTH
		|| a.y > 3 * WIN_WIDTH || b.x < -2 * WIN_WIDTH || a.x < -2 * WIN_WIDTH
		|| b.y < -2 * WIN_WIDTH || a.y < -2 * WIN_WIDTH)
		return ;
	init_draw_prm(&draw_prm, a, b);
	init_grad_prm(&grad_prm, a, b);
	while (a.x != b.x || a.y != b.y)
	{
		put_pixel(fdf, img, &a, &grad_prm);
		draw_prm.error2 = draw_prm.error << 1;
		if (draw_prm.error2 > -draw_prm.dy)
		{
			draw_prm.error -= draw_prm.dy;
			a.x += draw_prm.sign_x;
		}
		if (draw_prm.error2 < draw_prm.dx)
		{
			draw_prm.error += draw_prm.dx;
			a.y += draw_prm.sign_y;
		}
	}
	put_pixel(fdf, img, &b, &grad_prm);
}
