/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 22:59:50 by nick              #+#    #+#             */
/*   Updated: 2022/04/03 17:21:51 by nick             ###   ########.fr       */
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

# define RED_HIGH 185
# define BLUE_HIGH 0
# define RED_LOW 42
# define BLUE_LOW 156

# define RED_MASK 0xff0000
# define BLUE_MASK 0xff

# define COS_PI_3 0.866025f
# define SIN_PI_6 0.5f

# define INIT_DELAY 1000000000

# define MOUSE_SENSIVITY 0.5f

# define SHIFT_VALUE 8
# define ZOOM_IN_VALUE 1.05f
# define ZOOM_OUT_VALUE 0.95f

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_P 112
# define KEY_C 99
# define KEY_G 103
# define KEY_H 104
# define KEY_ESC 65307
# define KEY_PLUS 61
# define KEY_MINUS 45
# define KEY_NUM_PLUS 65451
# define KEY_NUM_MINUS 65453

# define BTN_LCM 1
# define BTN_MCM 2
# define BTN_RCM 3
# define BTN_UP 4
# define BTN_DOWN 5

# include <stdbool.h>

typedef enum e_proj
{
	ISOMETRIC,
	SPHERIC
}	t_proj;

typedef enum e_rot_center
{
	GLOABAL,
	LOCAL
}	t_rot_center;

typedef enum e_mouse_btn
{
	LCM = BTN_LCM,
	MCM = BTN_MCM,
	RCM = BTN_RCM,
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
	int				height_max;
	int				height_min;
	float			shift3d_x;
	float			shift3d_y;
	float			angle_z_global;
	float			angle_z_local;
	float			height_scale;
	float			zoom;
	float			radius;

	int				last_cursor_click_x;
	int				last_cursor_click_y;
	t_mouse_btn		pressed_mouse_btn;

	t_proj			proj;
	t_rot_center	rot_center;
	bool			is_grad_on;
	bool			is_height_map;
}	t_fdf;

t_point_3d	**alloc_matrix_3d(int height, int width);
t_point_2d	**alloc_matrix_2d(int height, int width);
void		free_matrix_3d(t_point_3d **matrix_3d, int height);
void		free_matrix_2d(t_point_2d **matrix_2d, int height);

void		scale_map(t_fdf *fdf, float scale);
void		shift_map(t_fdf *fdf, int x, int y);
void		rotate_map(t_fdf *fdf, float value);
void		increase_map_height(t_fdf *fdf, float value);

#endif
