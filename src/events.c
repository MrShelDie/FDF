/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 19:42:21 by nick              #+#    #+#             */
/*   Updated: 2022/03/24 23:47:50 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

#include "fdf.h"
#include "render.h"

// int	mouse_hook(int button, int x, int y, void *param)
// {
// 	if (button == LCM)

// }

// int	key_hook(int keycode, void *param)
// {
// 	if (keycode == KEY_W)
// 		((t_fdf *)param)->shift_y -= SHIFT_VALUE;
// 	else if (keycode == KEY_S)
// 		((t_fdf *)param)->shift_y += SHIFT_VALUE;
// 	else if (keycode == KEY_D)
// 		((t_fdf *)param)->shift_x += SHIFT_VALUE;
// 	else if (keycode == KEY_A)
// 		((t_fdf *)param)->shift_x -= SHIFT_VALUE;
// 	render(param);
// }

int	key_press(int keycode, void *param)
{
	if (keycode == KEY_W)
		shift_map(param, SHIFT_VALUE, SHIFT_VALUE);
		// ((t_fdf *)param)->shift_y += SHIFT_VALUE;
	else if (keycode == KEY_S)
		shift_map(param, -SHIFT_VALUE, -SHIFT_VALUE);
		// ((t_fdf *)param)->shift_y -= SHIFT_VALUE;
	else if (keycode == KEY_D)
		shift_map(param, -SHIFT_VALUE, SHIFT_VALUE);
		// ((t_fdf *)param)->shift_x -= SHIFT_VALUE;
	else if (keycode == KEY_A)
		shift_map(param, SHIFT_VALUE, -SHIFT_VALUE);
		// ((t_fdf *)param)->shift_x += SHIFT_VALUE;
}

int	button_press(int button, int x, int y, void *param)
{
	if (button == BTN_UP)
		scale_map(param, ZOOM_IN_VALUE);
	else if (button == BTN_DOWN)
		scale_map(param, ZOOM_OUT_VALUE);
	// if (button == BTN_UP)
	// 	((t_fdf *)param)->zoom += ZOOM_IN_VALUE;
	// else if (button == BTN_DOWN)
	// 	((t_fdf *)param)->zoom -= ZOOM_OUT_VALUE;
	else if (((t_fdf *)param)->pressed_mouse_btn == NONE)
	{
		if (button == BTN_LCM)
			((t_fdf *)param)->pressed_mouse_btn = BTN_LCM;
		else if (button == BTN_MCM)
			((t_fdf *)param)->pressed_mouse_btn = BTN_MCM;
		((t_fdf *)param)->last_cursor_click_x = x;
		((t_fdf *)param)->last_cursor_click_y = y;
	}
}

int	button_release(int button, int x, int y, void *param)
{
	if (button == ((t_fdf *)param)->pressed_mouse_btn)
		((t_fdf *)param)->pressed_mouse_btn = NONE;
}

// int	mouse_movement(int x, int y, void *param)
// {
// 	int	dx;
// 	int	dy;

// 	dx = (x - ((t_fdf *)param)->last_cursor_click_x);
// 	dy = (y - ((t_fdf *)param)->last_cursor_click_y);
// 	// int dx1 = x - ((t_fdf *)param)->last_cursor_click_x;
// 	// int dy1 = y - ((t_fdf *)param)->last_cursor_click_y;
// 	// dx = 0.577354 * dx1 + dy1;
// 	// dy = -0.577354 * dx1 + dy1;
// 	if (((t_fdf *)param)->pressed_mouse_btn == MKM)
// 	{
// 		((t_fdf *)param)->shift_x += dx;
// 		((t_fdf *)param)->shift_y += dy;
// 		((t_fdf *)param)->last_cursor_click_x = x;
// 		((t_fdf *)param)->last_cursor_click_y = y;
// 		//shift_map(param, dx, dy);
// 	}
// }

int	mouse_movement(int x, int y, void *param)
{
	int	dx;
	int	dy;

	// dx = (x - ((t_fdf *)param)->last_cursor_click_x);
	// dy = (y - ((t_fdf *)param)->last_cursor_click_y);
	int dx1 = x - ((t_fdf *)param)->last_cursor_click_x;
	int dy1 = y - ((t_fdf *)param)->last_cursor_click_y;
	dx = 0.577354 * dx1 + dy1;
	dy = -0.577354 * dx1 + dy1;
	if (((t_fdf *)param)->pressed_mouse_btn == MCM)
	{
		// ((t_fdf *)param)->shift_x += dx;
		// ((t_fdf *)param)->shift_y += dy;
		((t_fdf *)param)->last_cursor_click_x = x;
		((t_fdf *)param)->last_cursor_click_y = y;
		shift_map(param, dx, dy);
	}
	else if (((t_fdf *)param)->pressed_mouse_btn == LCM)
	{
		((t_fdf *)param)->last_cursor_click_x = x;
		((t_fdf *)param)->last_cursor_click_y = y;
		((t_fdf *)param)->angle_z += -dx1 / 200.0;
		// ((t_fdf *)param)->angle_x += -dy / 200.0;
		// rotate_z_3d(param, dx1 / 200.0);
	}
}

int	loop_hook(void *param)
{
	// ((t_fdf *)param)->angle_z += 0.001;
	render(param);
}
