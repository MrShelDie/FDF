/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   def.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 22:59:50 by nick              #+#    #+#             */
/*   Updated: 2022/03/05 13:42:28 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEF_H
# define DEF_H

# define TRUE 1
# define FALSE 0

# define SUCCESS 1
# define ERROR 0

typedef struct s_point
{
	float			x;
	float			y;
	float			z;
	unsigned int	color;
	int				is_color_default;
}	t_point;

typedef struct s_fdf
{
	int		height;
	int		width;
	t_point	**matrix;
}	t_fdf;

#endif
