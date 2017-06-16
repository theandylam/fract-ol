/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alam <alam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 19:02:35 by alam              #+#    #+#             */
/*   Updated: 2017/04/28 16:52:41 by alam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdlib.h>
# include <math.h>
# include <mlx.h>
# include <pthread.h>
# include "libft/libft.h"

# define WIN_X 500
# define WIN_Y 660

# define MAX_X 500
# define MAX_Y 500
# define MAX_THREADS 8
# define MAX_ITER 256

# define C_RE 0.285f
# define C_IM 0.01f
# define NEWTON_TOL 0.000001f

# define CYAN 0x0000FFFF
# define MAGENTA 0x00FF00FF
# define YELLOW 0x00FFFF00
# define WHITE 0x00FFFFFF
# define PURPLE 0x008A2BE2
# define RED 0x00FF0000
# define BLUE 0x0000FF00
# define GREEN 0x000000FF

# define R_MSK 0x00FF0000
# define G_MSK 0x0000FF00
# define B_MSK 0x000000FF

# define LEFT_CLICK 1
# define RIGHT_CLICK 2
# define SCRL_UP 4
# define SCRL_DN 5

# define ESC 53
# define W_KEY 13
# define A_KEY 0
# define S_KEY 1
# define D_KEY 2
# define Q_KEY 12
# define E_KEY 14
# define UP 126
# define DOWN 125
# define LEFT 123
# define RIGHT 124
# define NUM_PLUS 69
# define NUM_MINUS 78
# define SPACEBAR 49
# define TILDE 50

# define INCORRECT_PARAM 1
# define MLX_INIT_ERR 2
# define MLX_WIN_ERR 3
# define P_THREAD_CREATE 4
# define P_THREAD_JOIN 5
# define INVALID_THREAD_COUNT 6
# define IMG_CREATE_ERR 7
# define IMG_DATA_ERR 8

typedef struct	s_vec
{
	double x;
	double y;
	double z;
}				t_vec;

typedef struct	s_map
{
	float	xmax;
	float	ymax;
	float	zmax;
	int		base_color;
	int		top_color;
	int		color[MAX_X][MAX_Y];
	t_vec	pt[MAX_X][MAX_Y];
}				t_map;

typedef struct	s_mlx
{
	void *mlx;
	void *win;
}				t_mlx;

typedef struct	s_img
{
	void	*ptr;
	char	*addr;
	int		bpp;
	int		line_size;
	int		endian;
	int		xmax;
	int		ymax;
}				t_img;

typedef struct	s_frame
{
	void			*mlx;
	void			*win;

	t_img			img;

	int				fract;
	t_vec			c;
	t_vec			r1;
	t_vec			r2;
	t_vec			r3;
	double			x_shift;
	double			y_shift;
	double			scale;
	int				julia_mouse_movement;
	int				mouse_1_drag;

	pthread_mutex_t	quadrant_mutex;
	int				quadrant;
}				t_frame;

/*
**				-----------------
**				|	fractol.c	|
**				-----------------
*/
void			exit_program(int code);

/*
**				-----------------
**				|	init.c		|
**				-----------------
*/
void			init_fractal_param(t_frame *frm);
void			setup_window(t_frame *frm, char **argv);
int				get_fractol_type(char **argv);

/*
**				-----------------
**				|	draw.c		|
**				-----------------
*/
t_vec			xform_pt(t_vec pt, t_frame frm);
void			draw_fractol_mt(t_frame frm);

/*
**				-----------------
**				|	color.c		|
**				-----------------
*/
int				gradient(double iter, int max, int bot_c, int top_c);
int				color(double iter);

/*
**				-----------------
**				|	fractals	|
**				-----------------
*/
double			julia(t_vec pt, t_frame frm);
double			mandelbrot(t_vec pt, t_frame frm);
int				newton(t_vec pt, t_frame frm);

/*
**				-----------------
**				|	image.c		|
**				-----------------
*/
void			new_image(t_frame *frm, int x, int y);
void			img_pxl_put(t_frame frm, int x, int y, int color);

/*
**				-----------------
**				|	hooks.c		|
**				-----------------
*/
int				key_hook(int key, t_frame *frm);
int				mouse_hook(int button, int x, int y, t_frame *frm);
int				release_hook(int button, int x, int y, t_frame *frm);
int				mouse_motion_hook(int x, int y, t_frame *frm);
int				expose_hook(t_frame *frm);

/*
**				-----------------
**				|	key.c		|
**				-----------------
*/
int				check_key(int key);
void			change_julia_param(int key, t_frame *frm);
void			move_map(int key, t_frame *frm);
void			change_scale(int key, t_frame *frm);
void			reset(t_frame *frm);

/*
**				-----------------
**				|	mouse.c		|
**				-----------------
*/
void			mouse_zoom(int button, int x, int y, t_frame *frm);

/*
**				-----------------
**				|	ui.c		|
**				-----------------
*/
void			draw_ui(t_frame frm);

#endif
