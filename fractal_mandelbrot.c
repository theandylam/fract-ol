/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_mandelbrot.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alam <alam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 14:48:39 by alam              #+#    #+#             */
/*   Updated: 2017/04/28 14:38:07 by alam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double	mandelbrot(t_vec pt, t_frame frm)
{
	int		i;
	t_vec	z;
	t_vec	z_0;
	double	out;
	double	dist_sqrd;

	i = 0;
	z.x = 0;
	z.y = 0;
	dist_sqrd = 0;
	pt = xform_pt(pt, frm);
	while ((dist_sqrd < 4) && (i < MAX_ITER))
	{
		z_0.x = z.x;
		z_0.y = z.y;
		z.x = (z_0.x * z_0.x) - (z_0.y * z_0.y) + pt.x;
		z.y = (2 * z_0.x * z_0.y) + pt.y;
		if (z.x == z_0.x && z.y == z_0.y)
			return (MAX_ITER);
		dist_sqrd = (z.x * z.x) + (z.y * z.y);
		i++;
	}
	out = (i == MAX_ITER) ? i : i + 1 - ((log((log(dist_sqrd) / 2) / log(2)))
																	/ log(2));
	return (out);
}
