/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alam <alam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 14:48:39 by alam              #+#    #+#             */
/*   Updated: 2017/04/28 16:46:23 by alam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	get_quadrant(int quad, t_vec *start, t_vec *stop)
{
	if (MAX_THREADS == 4)
	{
		start->x = (quad % 2 == 0) ? 0 : (MAX_X / 2);
		start->y = (quad < 2) ? 0 : (MAX_Y / 2);
		stop->x = (quad % 2 == 0) ? (MAX_X / 2) : MAX_X;
		stop->y = (quad < 2) ? (MAX_Y / 2) : MAX_Y;
	}
	else if (MAX_THREADS == 8)
	{
		start->x = (quad % 4) * (MAX_X / 4);
		start->y = (quad < 4) ? 0 : (MAX_Y / 2);
		stop->x = ((quad % 4) + 1) * (MAX_X / 4);
		stop->y = (quad < 4) ? (MAX_Y / 2) : MAX_Y;
	}
	else
		exit_program(INVALID_THREAD_COUNT);
}

static void	img_fractal_put(t_vec pt, t_frame frm)
{
	if (frm.fract == 0)
		img_pxl_put(frm, pt.x, pt.y, color(julia(pt, frm)));
	else if (frm.fract == 1)
		img_pxl_put(frm, pt.x, pt.y, color(mandelbrot(pt, frm)));
	else if (frm.fract == 2)
		img_pxl_put(frm, pt.x, pt.y, newton(pt, frm));
}

static void	*fractol_map_mt(void *frm)
{
	t_vec	pt;
	t_vec	start;
	t_vec	stop;

	pthread_mutex_lock(&((t_frame *)frm)->quadrant_mutex);
	get_quadrant(((t_frame *)frm)->quadrant, &start, &stop);
	((t_frame *)frm)->quadrant++;
	pthread_mutex_unlock(&((t_frame *)frm)->quadrant_mutex);
	pt.y = start.y;
	pt.z = 0;
	while (pt.y < stop.y)
	{
		pt.x = start.x;
		while (pt.x < stop.x)
		{
			img_fractal_put(pt, *(t_frame *)frm);
			pt.x++;
		}
		pt.y++;
	}
	return (NULL);
}

t_vec		xform_pt(t_vec pt, t_frame frm)
{
	pt.x = 1.5 * (pt.x - MAX_X / 2) / (frm.scale * MAX_X / 2) + frm.x_shift;
	pt.y = 1.5 * (pt.y - MAX_Y / 2) / (frm.scale * MAX_Y / 2) + frm.y_shift;
	pt.z = 0;
	return (pt);
}

void		draw_fractol_mt(t_frame frm)
{
	int			i;
	pthread_t	fract_thread[MAX_THREADS];

	i = 0;
	while (i < MAX_THREADS)
	{
		if (pthread_create(&fract_thread[i], NULL, fractol_map_mt, &frm))
			exit_program(P_THREAD_CREATE);
		i++;
	}
	i = 0;
	while (i < MAX_THREADS)
	{
		if (pthread_join(fract_thread[i], NULL))
			exit_program(P_THREAD_JOIN);
		i++;
	}
	mlx_put_image_to_window(frm.mlx, frm.win, frm.img.ptr, 0, 0);
}
