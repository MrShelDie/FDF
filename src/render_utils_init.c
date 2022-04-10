/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils_init.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 16:32:10 by nick              #+#    #+#             */
/*   Updated: 2022/04/10 16:38:33 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "render_utils.h"

static int	get_sign(int a, int b)
{
	if (a < b)
		return (1);
	else
		return (-1);
}

void	init_draw_prm(t_draw_prm *prm, t_point_2d a, t_point_2d b)
{
	prm->dx = abs(b.x - a.x);
	prm->dy = abs(b.y - a.y);
	prm->sign_x = get_sign(a.x, b.x);
	prm->sign_y = get_sign(a.y, b.y);
	prm->error = prm->dx - prm->dy;
}

void	init_grad_prm(t_grad_prm *prm, t_point_2d a, t_point_2d b)
{
	float	total_step;

	if (abs(b.x - a.x) > abs(b.y - a.y))
		total_step = abs(b.x - a.x);
	else
		total_step = abs(b.y - a.y);
	if (total_step == 0)
		total_step = 1;
	prm->red_a = a.color >> 16 & 0xff;
	prm->green_a = a.color >> 8 & 0xff;
	prm->blue_a = a.color & 0xff;
	prm->red_step = ((b.color >> 16 & 0xff) - prm->red_a) / total_step;
	prm->green_step = ((b.color >> 8 & 0xff) - prm->green_a) / total_step;
	prm->blue_step = ((b.color & 0xff) - prm->blue_a) / total_step;
	prm->curr_step = 0;
}
