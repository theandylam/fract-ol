/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_julia.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alam <alam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 14:48:39 by alam              #+#    #+#             */
/*   Updated: 2017/04/28 14:37:55 by alam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double	julia(t_vec pt, t_frame frm)
{
	int		i;
	t_vec	z;
	t_vec	z_0;
	double	out;
	double	dist_sqrd;

	i = 0;
	z = xform_pt(pt, frm);
	dist_sqrd = 0;
	while ((dist_sqrd < 4) && (i < MAX_ITER))
	{
		z_0.x = z.x;
		z_0.y = z.y;
		z.x = (z_0.x * z_0.x) - (z_0.y * z_0.y) + frm.c.x;
		z.y = (2 * z_0.x * z_0.y) + frm.c.y;
		dist_sqrd = (z.x * z.x) + (z.y * z.y);
		i++;
	}
	out = (i == MAX_ITER) ? i : i + 1 - ((log((log(dist_sqrd) / 2) / log(2)))
																	/ log(2));
	return (out);
}
