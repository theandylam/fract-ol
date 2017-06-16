/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_newton.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alam <alam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 14:48:39 by alam              #+#    #+#             */
/*   Updated: 2017/04/28 14:37:36 by alam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static t_vec	newton_funct(t_vec z)
{
	t_vec	z_0;

	z_0 = z;
	z.x = z_0.x - (pow(z_0.x, 5) + (z_0.x * pow(z_0.y, 4))
					+ (2 * pow(z_0.x, 3) * pow(z_0.y, 2)) - pow(z_0.x, 2)
					+ pow(z_0.y, 2)) / z_0.z;
	z.y = z_0.y - (pow(z_0.y, 5) + (z_0.y * pow(z_0.x, 4))
					+ (2 * pow(z_0.x, 2) * pow(z_0.y, 3))
					+ (2 * z_0.x * z_0.y)) / z_0.z;
	return (z);
}

static double	distance_squared(t_vec pt1, t_vec pt2)
{
	return (pow(pt1.x - pt2.x, 2) + pow(pt1.y - pt2.y, 2));
}

static int		check_roots(t_vec z, t_frame frm)
{
	double	tol_sqrd;

	tol_sqrd = NEWTON_TOL * NEWTON_TOL;
	if (distance_squared(z, frm.r1) <= tol_sqrd)
		return (1);
	else if (distance_squared(z, frm.r2) <= tol_sqrd)
		return (2);
	else if (distance_squared(z, frm.r3) <= tol_sqrd)
		return (3);
	else
		return (0);
}

static int		newton_color(double iter, int root)
{
	iter = 1 - exp(-iter / 4);
	iter *= MAX_ITER;
	if (root == 1)
		return (gradient(iter, MAX_ITER, WHITE, YELLOW));
	else if (root == 2)
		return (gradient(iter, MAX_ITER, WHITE, CYAN));
	else if (root == 3)
		return (gradient(iter, MAX_ITER, WHITE, MAGENTA));
	else
		return (WHITE);
}

int				newton(t_vec pt, t_frame frm)
{
	int		i;
	t_vec	z;
	t_vec	z_0;
	int		root;

	i = 0;
	z = xform_pt(pt, frm);
	while (i < MAX_ITER)
	{
		z_0 = z;
		z_0.z = 3 * pow(pow(z_0.x, 2) + pow(z_0.y, 2), 2);
		z = newton_funct(z_0);
		root = check_roots(z, frm);
		i++;
		if (root > 0)
			break ;
	}
	return (newton_color(i, root));
}
