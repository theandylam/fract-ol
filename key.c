/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alam <alam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 14:04:24 by alam              #+#    #+#             */
/*   Updated: 2017/04/28 16:10:30 by alam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		check_key(int key)
{
	if (key == W_KEY || key == A_KEY || key == S_KEY || key == D_KEY)
		return (1);
	else if (key == UP || key == DOWN || key == LEFT || key == RIGHT)
		return (2);
	else if (key == NUM_PLUS || key == NUM_MINUS)
		return (3);
	else if (key == SPACEBAR)
		return (4);
	else if (key == TILDE)
		return (5);
	else
		return (0);
}

void	change_julia_param(int key, t_frame *frm)
{
	if (key == UP)
		frm->c.y += 0.0001f;
	else if (key == DOWN)
		frm->c.y -= 0.0001f;
	else if (key == LEFT)
		frm->c.x -= 0.0001f;
	else if (key == RIGHT)
		frm->c.x += 0.0001f;
	draw_fractol_mt(*frm);
}

void	move_map(int key, t_frame *frm)
{
	if (key == W_KEY)
		frm->y_shift -= .005 / frm->scale;
	else if (key == A_KEY)
		frm->x_shift -= .005 / frm->scale;
	else if (key == S_KEY)
		frm->y_shift += .005 / frm->scale;
	else if (key == D_KEY)
		frm->x_shift += .005 / frm->scale;
	draw_fractol_mt(*frm);
}

void	change_scale(int key, t_frame *frm)
{
	if (key == NUM_PLUS)
		frm->scale *= 1.1;
	else if (key == NUM_MINUS)
		frm->scale *= 0.9;
	draw_fractol_mt(*frm);
}

void	reset(t_frame *frm)
{
	frm->scale = 1;
	frm->x_shift = (frm->fract == 1) ? -0.75 : 0;
	frm->y_shift = 0;
	frm->c.x = C_RE;
	frm->c.y = C_IM;
	frm->c.z = 0;
	draw_fractol_mt(*frm);
}
