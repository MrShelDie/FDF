/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 22:59:50 by nick              #+#    #+#             */
/*   Updated: 2022/03/24 07:54:44 by nick             ###   ########.fr       */
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
# define COS_PI_3 0.866025f
# define SIN_PI_6 0.5f

# define INIT_DELAY 100000000

# define MOUSE_SENSIVITY 0.5f

# define SHIFT_VALUE 8
# define ZOOM_IN_VALUE 1.05f
# define ZOOM_OUT_VALUE 0.95f

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100

# define BTN_LCM 1
# define BTN_MCM 2
# define BTN_UP 4
# define BTN_DOWN 5

typedef enum e_projection
{
	ISOMETRIC,
	PARALLEL
}	t_projection;

typedef enum e_mouse_btn
{
	LCM = BTN_LCM,
	MCM = BTN_MCM,
	NONE = 0
}	t_mouse_btn;

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

typedef struct s_point
{
	float	x;
	float	y;
	float	z;
}	t_point;

typedef struct s_fdf
{
	int				map_height;
	int				map_width;
	t_point_3d		**matrix_3d;
	t_point_2d		**matrix_2d;

	void			*mlx_ptr;
	void			*win_ptr;

	int				shift_x;
	int				shift_y;
	// float			angle_x;
	// float			angle_y;
	float			angle_z;
	float			height_scale;
	float			zoom;
	float			radius;

	int				last_cursor_click_x;
	int				last_cursor_click_y;
	t_mouse_btn		pressed_mouse_btn;

	t_projection	projection;
}	t_fdf;

t_point_3d	**alloc_matrix_3d(int height, int width);
t_point_2d	**alloc_matrix_2d(int height, int width);
void		free_matrix_3d(t_point_3d **matrix_3d, int height);
void		free_matrix_2d(t_point_2d **matrix_2d, int height);

void		scale_map(t_fdf *fdf, float scale);
void		shift_map(t_fdf *fdf, int x, int y);

#endif
