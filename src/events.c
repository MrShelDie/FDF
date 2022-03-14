/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 19:42:21 by nick              #+#    #+#             */
/*   Updated: 2022/03/14 22:10:22 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <unistd.h>
// #include "libft.h"

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
		((t_fdf *)param)->shift_y -= SHIFT_VALUE;
	else if (keycode == KEY_S)
		((t_fdf *)param)->shift_y += SHIFT_VALUE;
	else if (keycode == KEY_D)
		((t_fdf *)param)->shift_x += SHIFT_VALUE;
	else if (keycode == KEY_A)
		((t_fdf *)param)->shift_x -= SHIFT_VALUE;
	render(param);
}
