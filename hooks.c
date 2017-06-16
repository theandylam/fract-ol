/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alam <alam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 14:25:58 by alam              #+#    #+#             */
/*   Updated: 2017/04/28 14:49:42 by alam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	key_hook(int key, t_frame *frm)
{
	if (key == ESC || frm == NULL)
		exit_program(0);
	else if (check_key(key) == 1)
		move_map(key, frm);
	else if (check_key(key) == 2)
		change_julia_param(key, frm);
	else if (check_key(key) == 3)
		change_scale(key, frm);
	else if (check_key(key) == 4)
		frm->julia_mouse_movement ^= 1;
	else if (check_key(key) == 5)
		reset(frm);
	return (0);
}

int	mouse_hook(int button, int x, int y, t_frame *frm)
{
	if (button == SCRL_UP || button == SCRL_DN)
		mouse_zoom(button, x, y, frm);
	if (button == LEFT_CLICK)
		frm->mouse_1_drag = 1;
	return (0);
}

int	release_hook(int button, int x, int y, t_frame *frm)
{
	if (button == LEFT_CLICK)
		frm->mouse_1_drag = 0;
	x = y;
	return (0);
}

int	mouse_motion_hook(int x, int y, t_frame *frm)
{
	static t_vec	last_pt;
	t_vec			cur;

	cur.x = x;
	cur.y = y;
	if (frm->julia_mouse_movement != 0 && frm->fract == 0)
	{
		frm->c.x += 0.000001f * (x - last_pt.x);
		frm->c.y += 0.000001f * (y - last_pt.y);
	}
	if (frm->mouse_1_drag != 0)
	{
		cur = xform_pt(cur, *frm);
		last_pt = xform_pt(last_pt, *frm);
		frm->x_shift += last_pt.x - cur.x;
		frm->y_shift += last_pt.y - cur.y;
	}
	last_pt.x = x;
	last_pt.y = y;
	draw_fractol_mt(*frm);
	return (0);
}

int	expose_hook(t_frame *frm)
{
	draw_fractol_mt(*frm);
	return (0);
}
