/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabraham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 23:09:13 by vabraham          #+#    #+#             */
/*   Updated: 2020/01/31 16:40:16 by vabraham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ordinate(t_lst *t, int l, int k)
{
	mnoj(t, &(t->x0), &(t->y0), &(t->z0));
	mnoj(t, &(t->x1), &(t->y1), &(t->z1));
	if (l > 0)
	{
		t->z2 = t->matz[l - 1][k];
		if ((t->color_file)[l - 1][k] != -1)
			t->color2 = (t->color_file)[l - 1][k];
		t->z2_begin = t->z2;
		mnoj(t, &(t->x2), &(t->y2), &(t->z2));
		t->check_xy = 2;
		if ((t->z2 < t->zp && t->z0 < t->zp) || t->perspective == 0)
			draw_line(*t);
	}
}

void	home_0(t_lst *t, int l, int k)
{
	while (++k < t->len[l])
	{
		t->color0 = -1;
		t->color1 = -1;
		t->color2 = -1;
		t->x0 = t->a * k + t->a - (t->len[l] / 2) * t->a;
		t->x2 = t->x0;
		t->y1 = t->a * l + t->a - (t->len[l] / 2) * t->a;
		t->y0 = t->y1;
		t->z0 = t->matz[l][k];
		if ((t->color_file)[l][k] != -1)
			t->color0 = (t->color_file)[l][k];
		t->z0_begin = t->z0;
		t->x1 = t->a * (k + 1) + t->a - (t->len[l] / 2) * t->a;
		t->y2 = t->a * (l - 1) + t->a - (t->len[l] / 2) * t->a;
		t->z1 = t->matz[l][k + 1];
		if (k < t->len[l] - 1 && (t->color_file)[l][k + 1] != -1)
			t->color1 = (t->color_file)[l][k + 1];
		t->z1_begin = t->z1;
		ordinate(t, l, k);
		t->check_xy = 1;
		if (((t->z1 < t->zp && t->z0 < t->zp)
			|| t->perspective == 0) && k < t->len[l] - 1)
			draw_line(*t);
	}
}

void	home(t_lst *lst)
{
	int l;

	lst->matriy[0][0] = 1;
	lst->matriy[1][1] = cos(lst->al_x);
	lst->matriy[1][2] = -sin(lst->al_x);
	lst->matriy[2][1] = sin(lst->al_x);
	lst->matriy[2][2] = cos(lst->al_x);
	lst->matrix[0][0] = cos(lst->al_y);
	lst->matrix[0][2] = sin(lst->al_y);
	lst->matrix[1][1] = 1;
	lst->matrix[2][0] = -sin(lst->al_y);
	lst->matrix[2][2] = cos(lst->al_y);
	lst->matriz[0][0] = cos(lst->al_z);
	lst->matriz[0][1] = -sin(lst->al_z);
	lst->matriz[1][0] = sin(lst->al_z);
	lst->matriz[1][1] = cos(lst->al_z);
	lst->matriz[2][2] = 1;
	l = -1;
	while (++l < lst->i)
		if (lst->color_file[l][0] == 0)
			lst->color_file[l][0] = -1;
	l = -1;
	while (++l < lst->i)
		home_0(lst, l, -1);
}

void	new_0(t_lst *lst, int t, int k)
{
	int ct;

	lst->min_z = 2147483647;
	lst->max_z = -2147483648;
	while ((lst->line)[++t])
	{
		k = 0;
		ct = 0;
		while ((lst->line)[t][k])
		{
			record(lst, t, k, &ct);
			while ((lst->line)[t][k] && (lst->line)[t][k] == ' ')
				k++;
			if ((lst->line)[t][k] && (lst->line)[t][k] == '-')
				k++;
			while ((lst->line)[t][k] && (lst->line)[t][k] >= '0'
				&& (lst->line)[t][k] <= '9')
				k++;
			if ((lst->line)[t][k] == ',')
			{
				check_color(lst->line[t], &k);
				(lst->color_file)[t][ct - 1] = ft_atoi_16((lst->line)[t], &k);
			}
		}
	}
}

int		new(t_lst *lst)
{
	fon(lst->data, FON);
	lst->al_x = 27 * 0.04;
	lst->al_y = 0;
	lst->al_z = -27 * 0.04;
	lst->per = 0;
	lst->color_b0 = BLUE;
	lst->color_e0 = RED;
	lst->color_fon = FON;
	lst->point = 0;
	lst->len = (int *)malloc(sizeof(int) * lst->i);
	if (!(lst->matz = (int **)malloc(sizeof(int *) * lst->i)) ||
		!(lst->color_file = (int **)malloc(sizeof(int *) * lst->i)))
		return (error());
	cycle(lst, lst->line);
	lst->perspective = 0;
	lst->zp = 800;
	new_0(lst, -1, 0);
	nul_matrix(lst);
	home(lst);
	return (1);
}
