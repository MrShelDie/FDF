/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 19:45:03 by nick              #+#    #+#             */
/*   Updated: 2022/04/09 21:51:31 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_H
# define EVENTS_H

//int	key_hook(int keycode, void *param);
//int	mouse_hook(int button, int x, int y, void *param);
int	ev_key_press(int keycode, t_fdf *fdf);
int	ev_button_press(int button, int x, int y, t_fdf *fdf);
int	ev_button_release(int button, int x, int y, t_fdf *fdf);
int	ev_mouse_movement(int x, int y, t_fdf *fdf);
int	ev_loop_hook(t_fdf *fdf);
int	ev_close(t_fdf *fdf);

#endif
