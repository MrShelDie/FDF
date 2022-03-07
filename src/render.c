/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 01:31:59 by nick              #+#    #+#             */
/*   Updated: 2022/03/07 15:39:09 by nick             ###   ########.fr       */
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
	struct timeval start1, end1;

	t_point_2d	a = {0, 0, 0xff0000};
	t_point_2d	b = {900, 900, 0xff0000};

	gettimeofday(&start1, NULL);
	draw_line(fdf, img, a, b);
	gettimeofday(&end1, NULL);

	double time_taken1 = end1.tv_sec + end1.tv_usec / 1e6 - start1.tv_sec - start1.tv_usec / 1e6; // in seconds

	printf("time program took %f seconds to execute 1\n", time_taken1);
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
	// проецирование
	draw_lines(fdf, &img);

	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, img.img_ptr, 0, 0);
	mlx_destroy_image(fdf->mlx_ptr, img.img_ptr);
}
