/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 19:42:21 by nick              #+#    #+#             */
/*   Updated: 2022/04/03 13:59:01 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

#include "fdf.h"
#include "render.h"

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

int	key_press(int keycode, t_fdf *fdf)
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
	// printf("%d\n", keycode);
}

int	button_press(int button, int x, int y, t_fdf *fdf)
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

int	button_release(int button, int x, int y, t_fdf *fdf)
{
	if (button == fdf->pressed_mouse_btn)
		fdf->pressed_mouse_btn = NONE;
}

void	set_delta_movement(
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

int	mouse_movement(int x, int y, t_fdf *fdf)
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

int	loop_hook(void *param)
{
	render(param);
}
