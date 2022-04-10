/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 21:48:12 by nick              #+#    #+#             */
/*   Updated: 2022/04/10 11:58:20 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "events.h"

static void	shift_isometric(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_W)
		shift_map(fdf, SHIFT_VALUE, SHIFT_VALUE);
	else if (keycode == KEY_S)
		shift_map(fdf, -SHIFT_VALUE, -SHIFT_VALUE);
	else if (keycode == KEY_D)
		shift_map(fdf, -SHIFT_VALUE, SHIFT_VALUE);
	else if (keycode == KEY_A)
		shift_map(fdf, SHIFT_VALUE, -SHIFT_VALUE);
}

static void	shift_spheric(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_W)
		shift_map(fdf, 0, SHIFT_VALUE);
	else if (keycode == KEY_S)
		shift_map(fdf, 0, -SHIFT_VALUE);
	else if (keycode == KEY_D)
		shift_map(fdf, -SHIFT_VALUE, 0);
	else if (keycode == KEY_A)
		shift_map(fdf, SHIFT_VALUE, 0);
}

static void	shift_proj(int keycode, t_fdf *fdf)
{
	if (fdf->proj == ISOMETRIC)
		shift_isometric(keycode, fdf);
	else if (fdf->proj == SPHERIC)
		shift_spheric(keycode, fdf);
}

int	ev_key_press(int keycode, t_fdf *fdf)
{
	shift_proj(keycode, fdf);
	if (keycode == KEY_P && fdf->proj == ISOMETRIC)
		fdf->proj = SPHERIC;
	else if (keycode == KEY_P && fdf->proj == SPHERIC)
		fdf->proj = ISOMETRIC;
	else if (keycode == KEY_PLUS || keycode == KEY_NUM_PLUS)
		increase_map_height(fdf, 7);
	else if (keycode == KEY_MINUS || keycode == KEY_NUM_MINUS)
		increase_map_height(fdf, -7);
	else if (keycode == KEY_C && fdf->rot_center == GLOABAL)
		fdf->rot_center = LOCAL;
	else if (keycode == KEY_C && fdf->rot_center == LOCAL)
		fdf->rot_center = GLOABAL;
	else if (keycode == KEY_G)
		fdf->is_grad_on = !fdf->is_grad_on;
	else if (keycode == KEY_H)
		fdf->is_height_map = !fdf->is_height_map;
	else if (keycode == SQUARE_BACK_BRACKET)
		increase_radius(fdf, -5);
	else if (keycode == SQUARE_BRACKET)
		increase_radius(fdf, 5);
	else if (keycode == KEY_ESC)
		ev_close(fdf);
}