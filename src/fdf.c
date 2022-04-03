/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 15:24:33 by nick              #+#    #+#             */
/*   Updated: 2022/04/03 16:46:59 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <X11/X.h>
#include <limits.h>

#include "mlx.h"
#include "fdf.h"
#include "libft.h"
#include "parser.h"
#include "render.h"
#include "events.h"

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
	fdf->height_max = INT_MIN;
	fdf->height_min = INT_MAX;
	if (!parse(fdf, file_name))
		return (ERROR);
	fdf->mlx_ptr = mlx_init();
	if (!fdf->mlx_ptr)
	{
		free_matrix_3d(fdf->matrix_3d, fdf->map_height);
		return (ERROR);
	}
	fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "FDF");
	if (!fdf->win_ptr)
	{
		free_matrix_3d(fdf->matrix_3d, fdf->map_height);
		return (ERROR);
	}
	fdf->shift_x = WIN_WIDTH / 2;
	fdf->shift_y = WIN_HEIGHT / 2;
	fdf->shift3d_x = 0;
	fdf->shift3d_y = 0;
	fdf->angle_z_global = 0;
	fdf->angle_z_local = 0;
	fdf->height_scale = 0.5;
	fdf->pressed_mouse_btn = NONE;
	fdf->zoom = 1;
	fdf->radius = WIN_HEIGHT;
	fdf->proj = ISOMETRIC;
	fdf->rot_center = LOCAL;
	fdf->is_grad_on = false;
}

static void	delay(int iter_nb)
{
	while (iter_nb-- > 0)
		;
}

static void	init_events(t_fdf *fdf)
{
	mlx_loop_hook(fdf->mlx_ptr, ev_loop_hook, fdf);
	mlx_hook(fdf->win_ptr, KeyPress, KeyPressMask, ev_key_press, fdf);
	mlx_hook(fdf->win_ptr, ButtonPress, ButtonPressMask, ev_button_press, fdf);
	mlx_hook(fdf->win_ptr, ButtonRelease,
		ButtonReleaseMask, ev_button_release, fdf);
	mlx_hook(fdf->win_ptr, MotionNotify,
		PointerMotionMask, ev_mouse_movement, fdf);
	mlx_hook(fdf->win_ptr, DestroyNotify, StructureNotifyMask, ev_close, fdf);
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	if (!check_args(argc, argv))
		return (0);
	if (!fdf_init(&fdf, argv[1]))
		return (0);
	shift_map(&fdf, -fdf.map_width / 2, -fdf.map_height / 2);
	scale_map(&fdf, WIN_HEIGHT / fdf.map_width * 0.8);
	delay(INIT_DELAY);
	init_events(&fdf);
	mlx_do_key_autorepeaton(fdf.mlx_ptr);
	mlx_do_sync(fdf.mlx_ptr);
	render(&fdf);
	mlx_loop(fdf.mlx_ptr);
	free_matrix_3d(fdf.matrix_3d, fdf.map_height);
	return (0);
}
