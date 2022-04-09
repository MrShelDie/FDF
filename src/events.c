/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 19:42:21 by nick              #+#    #+#             */
/*   Updated: 2022/04/09 20:06:42 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

#include "mlx.h"
#include "fdf.h"
#include "render.h"

int	ev_close(t_fdf *fdf)
{
	mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
	fdf->win_ptr = NULL;
}

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

int	ev_key_press(int keycode, t_fdf *fdf)
{
	if (fdf->proj == ISOMETRIC)
		shift_isometric(keycode, fdf);
	else if (fdf->proj == SPHERIC)
		shift_spheric(keycode, fdf);
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
		scale_radius(fdf, -5);
	else if (keycode == SQUARE_BRACKET)
		scale_radius(fdf, 5);
	else if (keycode == KEY_ESC)
		ev_close(fdf);
	// printf("%d\n", keycode);
}

int	ev_button_press(int button, int x, int y, t_fdf *fdf)
{
	if (button == BTN_UP)
		scale_map(fdf, ZOOM_IN_VALUE);
	else if (button == BTN_DOWN)
		scale_map(fdf, ZOOM_OUT_VALUE);
	else if (fdf->pressed_mouse_btn == NONE)
	{
		if (button == BTN_LCM)
			fdf->pressed_mouse_btn = BTN_LCM;
		else if (button == BTN_MCM)
			fdf->pressed_mouse_btn = BTN_MCM;
		else if (button == BTN_RCM)
			fdf->pressed_mouse_btn = BTN_RCM;
		fdf->last_cursor_click_x = x;
		fdf->last_cursor_click_y = y;
	}
}

int	ev_button_release(int button, int x, int y, t_fdf *fdf)
{
	if (button == fdf->pressed_mouse_btn)
		fdf->pressed_mouse_btn = NONE;
}

static void set_delta_movement(
	const t_fdf *fdf, const t_point_2d *p, int *dx, int *dy)
{
	int	dx1;
	int	dy1;

	dx1 = p->x - fdf->last_cursor_click_x;
	dy1 = p->y - fdf->last_cursor_click_y;
	if (fdf->proj == ISOMETRIC)
	{
		*dx = 0.577354 * dx1 + dy1;
		*dy = -0.577354 * dx1 + dy1;
	}
	else if (fdf->proj == SPHERIC)
	{
		*dx = dx1;
		*dy = dy1;
	}
}

int	ev_mouse_movement(int x, int y, t_fdf *fdf)
{
	int			dx;
	int			dy;
	t_point_2d	p;

	p.x = x;
	p.y = y;
	set_delta_movement(fdf, &p, &dx, &dy);
	if (fdf->pressed_mouse_btn == MCM || fdf->pressed_mouse_btn == LCM
		|| fdf->pressed_mouse_btn == RCM)
	{
		fdf->last_cursor_click_x = x;
		fdf->last_cursor_click_y = y;
	}
	if (fdf->pressed_mouse_btn == MCM)
		shift_map(fdf, dx, dy);
	else if (fdf->pressed_mouse_btn == LCM)
		rotate_map(fdf, -dx / 200.0);
	else if (fdf->pressed_mouse_btn == RCM)
		increase_map_height(fdf, -dy);
}

int	ev_loop_hook(void *param)
{
	render(param);
}
