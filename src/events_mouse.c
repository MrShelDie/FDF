/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 21:53:36 by nick              #+#    #+#             */
/*   Updated: 2022/04/10 15:33:26 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	return (0);
}

int	ev_button_release(int button, int x, int y, t_fdf *fdf)
{
	(void)x;
	(void)y;
	if (button == (int)fdf->pressed_mouse_btn)
		fdf->pressed_mouse_btn = NONE;
	return (0);
}

static void	set_delta_movement(
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
	else
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
	return (0);
}
