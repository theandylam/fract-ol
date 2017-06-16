/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alam <alam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 14:48:39 by alam              #+#    #+#             */
/*   Updated: 2017/04/28 15:22:35 by alam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init_fractal_param(t_frame *frm)
{
	if (frm->fract == 1)
		frm->x_shift = -0.75;
	else if (frm->fract == 2)
	{
		frm->r1.x = 1;
		frm->r1.y = 0;
		frm->r2.x = -0.5;
		frm->r2.y = sin(2 * M_PI / 3);
		frm->r3.x = -0.5;
		frm->r3.y = -sin(2 * M_PI / 3);
	}
}

void	setup_window(t_frame *frm, char **argv)
{
	frm->fract = get_fractol_type(argv);
	frm->mlx = mlx_init();
	if (frm->mlx == NULL)
		exit_program(MLX_INIT_ERR);
	frm->win = mlx_new_window(frm->mlx, WIN_X, WIN_Y, "Fract'ol");
	if (frm->win == NULL)
		exit_program(MLX_WIN_ERR);
	new_image(frm, MAX_X, MAX_Y);
	frm->x_shift = 0;
	frm->y_shift = 0;
	frm->quadrant = 0;
	frm->c.x = C_RE;
	frm->c.y = C_IM;
	frm->c.z = 0;
	frm->scale = 1;
	frm->julia_mouse_movement = 0;
	frm->mouse_1_drag = 0;
	init_fractal_param(frm);
}

int		get_fractol_type(char **argv)
{
	int fractal_type;

	fractal_type = -1;
	if (ft_strncmp(argv[1], "julia", 5) == 0)
		fractal_type = 0;
	else if (ft_strncmp(argv[1], "mandelbrot", 10) == 0)
		fractal_type = 1;
	else if (ft_strncmp(argv[1], "newton", 6) == 0)
		fractal_type = 2;
	else
		exit_program(INCORRECT_PARAM);
	return (fractal_type);
}
