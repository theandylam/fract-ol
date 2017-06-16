/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alam <alam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 14:48:39 by alam              #+#    #+#             */
/*   Updated: 2017/04/28 15:52:58 by alam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	exit_program(int code)
{
	if (code == 0)
		ft_printf("Closing program\n");
	else if (code == INCORRECT_PARAM)
		ft_printf("Usage: ./fractol [julia/mandelbrot/newton]\n");
	else if (code == MLX_INIT_ERR)
		ft_printf("Error: Failed to initialize mlx\n");
	else if (code == MLX_WIN_ERR)
		ft_printf("Error: Failed to create window\n");
	else if (code == P_THREAD_CREATE)
		ft_printf("Error: Failed to create thread\n");
	else if (code == P_THREAD_JOIN)
		ft_printf("Error: Failed to join threads\n");
	else if (code == INVALID_THREAD_COUNT)
		ft_printf("Error: Invalid MAX_THREADS value\n");
	else if (code == IMG_CREATE_ERR)
		ft_printf("Error: Failed to creating mlx image\n");
	else if (code == IMG_DATA_ERR)
		ft_printf("Error: Failed to get mlx image data\n");
	exit(0);
}

int		main(int argc, char **argv)
{
	t_frame	frm;

	if (argc != 2)
		exit_program(INCORRECT_PARAM);
	setup_window(&frm, argv);
	draw_fractol_mt(frm);
	draw_ui(frm);
	mlx_key_hook(frm.win, &key_hook, &frm);
	mlx_hook(frm.win, 6, 0, &mouse_motion_hook, &frm);
	mlx_hook(frm.win, 5, 0, &release_hook, &frm);
	mlx_mouse_hook(frm.win, &mouse_hook, &frm);
	mlx_expose_hook(frm.win, &expose_hook, &frm);
	mlx_loop(frm.mlx);
	return (0);
}
