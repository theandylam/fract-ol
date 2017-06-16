/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alam <alam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 14:04:24 by alam              #+#    #+#             */
/*   Updated: 2017/04/28 16:12:54 by alam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	draw_ui(t_frame frm)
{
	mlx_string_put(frm.mlx, frm.win, 10, 510, WHITE,
					"Move camera - WASD");
	mlx_string_put(frm.mlx, frm.win, 10, 530, WHITE,
					"              M1 Click/Drag");
	mlx_string_put(frm.mlx, frm.win, 10, 550, WHITE,
					"       Zoom - Numpad +-");
	mlx_string_put(frm.mlx, frm.win, 10, 570, WHITE,
					"              Scroll Wheel");
	mlx_string_put(frm.mlx, frm.win, 10, 590, WHITE,
					"          ~ - Reset");
	if (frm.fract != 0)
		return ;
	mlx_string_put(frm.mlx, frm.win, 10, 610, WHITE,
					"    [Space] - Toggle julia mouse movement");
	mlx_string_put(frm.mlx, frm.win, 10, 630, WHITE,
					"     Arrows - Change julia parameter");
}
