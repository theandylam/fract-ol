/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alam <alam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 14:04:24 by alam              #+#    #+#             */
/*   Updated: 2017/04/28 15:18:19 by alam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	mouse_zoom(int button, int x, int y, t_frame *frm)
{
	t_vec	pt;
	t_vec	old_pt;
	t_vec	new_pt;

	pt.x = x;
	pt.y = y;
	if (button == SCRL_UP)
	{
		old_pt = xform_pt(pt, *frm);
		frm->scale *= 1.1;
		new_pt = xform_pt(pt, *frm);
		frm->x_shift -= new_pt.x - old_pt.x;
		frm->y_shift -= new_pt.y - old_pt.y;
	}
	else if (button == SCRL_DN)
	{
		old_pt = xform_pt(pt, *frm);
		frm->scale *= 0.9;
		new_pt = xform_pt(pt, *frm);
		frm->x_shift += new_pt.x - old_pt.x;
		frm->y_shift += new_pt.y - old_pt.y;
	}
	draw_fractol_mt(*frm);
}
