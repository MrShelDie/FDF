/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 15:24:33 by nick              #+#    #+#             */
/*   Updated: 2022/03/10 02:04:17 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fdf.h"
#include "libft.h"
#include "parser.h"
#include "render.h"

static int	check_args(int argc, char **argv)
{
	size_t	file_name_len;

	if (argc != 2)
		return (ERROR);
	file_name_len = ft_strlen(argv[1]);
	if (file_name_len < 4)
		return (ERROR);
	if (ft_strncmp(&argv[1][file_name_len - 4], ".fdf", 5) != 0)
		return (ERROR);
	return (SUCCESS);
}

static int	fdf_init(t_fdf *fdf, const char *file_name)
{
	if (!parse(fdf, file_name))
		return (ERROR);
	fdf->mlx_ptr = mlx_init();
	if (!fdf->mlx_ptr)
	{
		free_matrix_3d(fdf->matrix_3d, fdf->height);
		return (ERROR);
	}
	fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "FDF");
	if (!fdf->win_ptr)
	{
		free_matrix_3d(fdf->matrix_3d, fdf->height);
		return (ERROR);
	}
	fdf->shift_x = WIN_WIDTH / 2;
	fdf->shift_y = WIN_HEIGHT / 2;
	fdf->angle = 0;
	fdf->iso_height_scale = ISO_HEIGHT_SCALE;
}

static void	delay(int iter_nb)
{
	while (iter_nb-- > 0)
		;
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	if (!check_args(argc, argv))
		return (0);
	if (!fdf_init(&fdf, argv[1]))
		return (0);
	shift_3d(&fdf, -fdf.width / 2, -fdf.height / 2);
	scale_3d(&fdf, WIN_HEIGHT / fdf.width * 0.8);
	delay(INIT_DELAY);

	while (1)
	{
		//rotate_z_3d(&fdf, 1);
		fdf.angle += 0.001;
		render(&fdf);
	}
	mlx_loop(fdf.mlx_ptr);
	free_matrix_3d(fdf.matrix_3d, fdf.height);
	return (0);
}
