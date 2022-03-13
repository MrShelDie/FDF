/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 22:59:50 by nick              #+#    #+#             */
/*   Updated: 2022/03/14 01:45:31 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define TRUE 1
# define FALSE 0

# define SUCCESS 1
# define ERROR 0

# define UNDEF_COLOR 0xffffffff
# define WIN_HEIGHT 720
# define WIN_WIDTH 1280

# define ISO_HEIGHT_SCALE 0.2f
# define ISO_COS_ALPHA 0.866025f
# define ISO_SIN_BETA 0.5f

# define INIT_DELAY 100000000

typedef enum e_projection
{
	ISOMETRIC,
	PARALLEL
}	t_projection;

typedef struct s_point_3d
{
	float	x;
	float	y;
	float	z;
	int		color;
}	t_point_3d;

typedef struct s_point_2d
{
	float	x;
	float	y;
	int		color;
}	t_point_2d;

typedef struct s_fdf
{
	int				map_height;
	int				map_width;
	int				shift_x;
	int				shift_y;
	float			angle_x;
	float			angle_y;
	float			angle_z;
	float			height_scale;
	t_point_3d		**matrix_3d;
	t_point_2d		**matrix_2d;

	void			*mlx_ptr;
	void			*win_ptr;

	t_projection	projection;
}	t_fdf;

t_point_3d	**alloc_matrix_3d(int height, int width);
t_point_2d	**alloc_matrix_2d(int height, int width);
void		free_matrix_3d(t_point_3d **matrix_3d, int height);
void		free_matrix_2d(t_point_2d **matrix_2d, int height);

void		scale_3d(t_fdf *fdf, float scale);
void		shift_3d(t_fdf *fdf, int x, int y);

#endif
