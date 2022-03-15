/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 19:45:03 by nick              #+#    #+#             */
/*   Updated: 2022/03/14 23:20:40 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_H
# define EVENTS_H

//int	key_hook(int keycode, void *param);
//int	mouse_hook(int button, int x, int y, void *param);
int	key_press(int keycode, void *param);
int	button_press(int button, int x, int y, void *param);
int	button_release(int button, int x, int y, void *param);
int	mouse_movement(int x, int y, void *param);
int	loop_hook(void *param);

#endif
