/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 01:31:59 by nick              #+#    #+#             */
/*   Updated: 2022/03/10 00:17:29 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TODO DELETE
#include <sys/time.h>
#include <stdio.h>

#include "mlx.h"
#include "fdf.h"
#include "render.h"
#include "render_utils.h"

static void	draw_lines(t_fdf *fdf, t_image *img)
{
	int	i;
	int	j;

	i = -1;
	while (++i < fdf->height)
	{
		j = -1;
		while (++j < fdf->width)
		{
			if (j < fdf->width - 1)
				draw_line(
					fdf, img, fdf->matrix_2d[i][j], fdf->matrix_2d[i][j + 1]);
			if (i < fdf->height - 1)
				draw_line(
					fdf, img, fdf->matrix_2d[i][j], fdf->matrix_2d[i + 1][j]);
		}
	}
}

void	render(t_fdf *fdf)
{
	t_image	img;

	img.img_ptr = mlx_new_image(fdf->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	if (!img.img_ptr)
		return ;
	img.buff = mlx_get_data_addr(
			img.img_ptr, &img.bits_per_pixel, &img.size_line, &img.endian);
	if (!img.buff)
	{
		mlx_destroy_image(fdf->mlx_ptr, img.img_ptr);
		return ;
	}
	isometric(fdf);
	draw_lines(fdf, &img);
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, img.img_ptr, 0, 0);
	mlx_destroy_image(fdf->mlx_ptr, img.img_ptr);
}
