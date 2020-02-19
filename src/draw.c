/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabraham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 23:17:28 by vabraham          #+#    #+#             */
/*   Updated: 2019/10/29 23:17:29 by vabraham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	line_x(t_lst lst, int x, int y)
{
	float	tmp;
	t_color	cl;

	tmp = abc(y, lst.y0) / abc(x, lst.x0);
	cl.er = 0;
	if (y - lst.y0 >= 0)
		cl.opt = 1;
	else
		cl.opt = -1;
	cl.xn = lst.x0;
	cl.color0 = lst.color_e;
	cl.color1 = lst.color_b;
	while (lst.x0 <= x)
	{
		if (lst.y0 < HEIGHT && lst.y0 >= 0 && lst.x0 < WIDTH && lst.x0 >= 0)
			lst.data[lst.y0 * WIDTH + lst.x0 + 1] =
			get_color(cl, cl.xn, x, lst.x0);
		cl.er += tmp;
		if (cl.er >= 0.5)
		{
			lst.y0 += cl.opt;
			cl.er -= 1;
		}
		(lst.x0)++;
	}
}

void	line_y(t_lst lst, int x, int y)
{
	float	tmp;
	t_color	cl;

	tmp = abc(x, lst.x0) / abc(y, lst.y0);
	cl.er = 0;
	if (x - lst.x0 >= 0)
		cl.opt = 1;
	else
		cl.opt = -1;
	cl.yn = lst.y0;
	cl.color0 = lst.color_e;
	cl.color1 = lst.color_b;
	while (lst.y0 <= y)
	{
		if (lst.y0 < HEIGHT && lst.y0 >= 0 && lst.x0 < WIDTH && lst.x0 >= 0)
			lst.data[lst.y0 * WIDTH + lst.x0 + 1] =
			get_color(cl, cl.yn, y, lst.y0);
		cl.er += tmp;
		if (cl.er >= 0.5)
		{
			lst.x0 += cl.opt;
			cl.er -= 1;
		}
		(lst.y0)++;
	}
}

void	change(t_lst lst, t_draw draw)
{
	int tmp;

	if ((abc(draw.y, lst.y0) / abc(draw.x, lst.x0) < 1 && lst.x0 > draw.x)
		|| (abc(draw.y, lst.y0) / abc(draw.x, lst.x0) >= 1 && lst.y0 > draw.y))
	{
		tmp = lst.x0;
		lst.x0 = draw.x;
		draw.x = tmp;
		tmp = lst.y0;
		lst.y0 = draw.y;
		draw.y = tmp;
		tmp = lst.color_b;
		lst.color_b = lst.color_e;
		lst.color_e = tmp;
	}
	if (abc(draw.y, lst.y0) / abc(draw.x, lst.x0) < 1)
		line_x(lst, draw.x, draw.y);
	else
		line_y(lst, draw.x, draw.y);
}

void	draw_line2(t_lst lst, t_draw draw, int z_begin)
{
	t_color cl;

	lst.x0 += SH_X;
	lst.y0 += SH_Y;
	if ((lst.x0 > WIDTH && draw.x > WIDTH) || (lst.x0 < 0 && draw.x < 0)
		|| (lst.y0 > HEIGHT && draw.y > HEIGHT) || (lst.y0 < 0 && draw.y < 0))
		return ;
	cl.color0 = lst.color_b0;
	cl.color1 = lst.color_e0;
	draw.z1 = z_begin;
	draw.z2 = lst.z0_begin;
	if (lst.color_b == -1)
		lst.color_b = get_color(cl, lst.min_z, lst.max_z, draw.z1);
	if (lst.color_e == -1)
		lst.color_e = get_color(cl, lst.min_z, lst.max_z, draw.z2);
	if (draw.z1 == 0)
		draw.z1 = 1;
	if (draw.z2 == 0)
		draw.z2 = 1;
	change(lst, draw);
}

void	draw_line(t_lst lst)
{
	int		z_begin;
	t_draw	draw;

	lst.color_b = -1;
	lst.color_e = -1;
	if (lst.color0 != -1)
		lst.color_e = lst.color0;
	if (lst.check_xy == 1)
	{
		draw.x = lst.x1 + SH_X;
		draw.y = lst.y1 + SH_Y;
		z_begin = lst.z1_begin;
		if (lst.color1 != -1)
			lst.color_b = lst.color1;
	}
	else
	{
		draw.x = lst.x2 + SH_X;
		draw.y = lst.y2 + SH_Y;
		z_begin = lst.z2_begin;
		if (lst.color2 != -1)
			lst.color_b = lst.color2;
	}
	draw_line2(lst, draw, z_begin);
}
