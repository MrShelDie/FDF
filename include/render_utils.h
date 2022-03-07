/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 10:58:57 by nick              #+#    #+#             */
/*   Updated: 2022/03/07 15:04:56 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_UTILS_H
# define RENDER_UTILS_H

# include "fdf.h"

# define MSF 1
# define LSF 0

typedef struct s_image
{
	void	*img_ptr;
	char	*buff;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}	t_image;

void	draw_line(t_fdf *fdf, t_image *img, t_point_2d a, t_point_2d b);

#endif
