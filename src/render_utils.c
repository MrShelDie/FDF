/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 12:35:49 by nick              #+#    #+#             */
/*   Updated: 2022/04/09 22:44:08 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>

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

// static void	init_grad_prm(
// 	t_grad_prm *prm, int color_a, int color_b, float total_step)
// {
// 	prm->red_a = color_a >> 16 & 0xff;
// 	prm->green_a = color_a >> 8 & 0xff;
// 	prm->blue_a = color_a & 0xff;
// 	prm->red_step = ((color_b >> 16 & 0xff) - prm->red_a) / total_step;
// 	prm->green_step = ((color_b >> 8 & 0xff) - prm->green_a) / total_step;
// 	prm->blue_step = ((color_b & 0xff) - prm->blue_a) / total_step;
// 	prm->curr_step = 0;
// }

static void	init_grad_prm(
	t_grad_prm *prm, t_point_2d *a, t_point_2d *b)
{
	float	total_step;

	if (abs(b->x - a->x) > abs(b->y - a->y))
		total_step = abs(b->x - a->x);
	else
		total_step = abs(b->y - a->y);
	if (total_step == 0)
		return ;
	prm->red_a = a->color >> 16 & 0xff;
	prm->green_a = a->color >> 8 & 0xff;
	prm->blue_a = a->color & 0xff;
	prm->red_step = ((b->color >> 16 & 0xff) - prm->red_a) / total_step;
	prm->green_step = ((b->color >> 8 & 0xff) - prm->green_a) / total_step;
	prm->blue_step = ((b->color & 0xff) - prm->blue_a) / total_step;
	prm->curr_step = 0;
}

// void	draw_line(t_fdf *fdf, t_image *img, t_point_2d a, t_point_2d b)
// {
// 	float		dx;
// 	float		dy;
// 	float		max;
// 	t_grad_prm	grad_prm;

// 	if (b.x > 3 * WIN_WIDTH || a.x > 3 * WIN_WIDTH || b.y > 3 * WIN_WIDTH
// 		|| a.y > 3 * WIN_WIDTH || b.x < -2 * WIN_WIDTH || a.x < -2 * WIN_WIDTH
// 		|| b.y < -2 * WIN_WIDTH || a.y < -2 * WIN_WIDTH)
// 		return ;
// 	dx = b.x - a.x;
// 	dy = b.y - a.y;
// 	if (fabs(dx) > fabs(dy))
// 		max = fabs(dx);
// 	else
// 		max = fabs(dy);
// 	dx /= max;
// 	dy /= max;
// 	init_grad_prm(&grad_prm, a.color, b.color, max);
// 	while ((int)(b.x - a.x) || (int)(b.y - a.y))
// 	{
// 		if (fdf->is_grad_on)
// 			interp_color(&grad_prm, &a);
// 		put_pixel(fdf, img, &a);
// 		a.x += dx;
// 		a.y += dy;
// 	}
// }

int	get_sign(int a, int b)
{
	if (a < b)
		return (1);
	else
		return (-1);
}

void	draw_line(t_fdf *fdf, t_image *img, t_point_2d a, t_point_2d b)
{
	int			dx;
	int			dy;
	int			sign_x;
	int			sign_y;
	int			error;
	int			error2;
	t_grad_prm	grad_prm;

	if (b.x > 3 * WIN_WIDTH || a.x > 3 * WIN_WIDTH || b.y > 3 * WIN_WIDTH
		|| a.y > 3 * WIN_WIDTH || b.x < -2 * WIN_WIDTH || a.x < -2 * WIN_WIDTH
		|| b.y < -2 * WIN_WIDTH || a.y < -2 * WIN_WIDTH)
		return ;
	dx = abs(b.x - a.x);
	dy = abs(b.y - a.y);
	sign_x = get_sign(a.x, b.x);
	sign_y = get_sign(a.y, b.y);
	error = dx - dy;
	init_grad_prm(&grad_prm, &a, &b);
	while (a.x != b.x || a.y != b.y)
	{
		put_pixel(fdf, img, &a, &grad_prm);
		error2 = error << 1;
		if (error2 > -dy)
		{
			error -= dy;
			a.x += sign_x;
		}
		if (error2 < dx)
		{
			error += dx;
			a.y += sign_y;
		}
	}
	put_pixel(fdf, img, &b, &grad_prm);
}
