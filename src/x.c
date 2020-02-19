/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabraham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 17:22:31 by vabraham          #+#    #+#             */
/*   Updated: 2020/02/02 22:18:53 by vabraham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		error(void)
{
	ft_putstr("Error\n");
	exit(1);
	return (0);
}

int		ussage(void)
{
	ft_putstr("usage: ./fdf <filename>\n");
	exit(1);
	return (0);
}

int		fill_in(t_lst *lst, char ***line, int i, char *name)
{
	int fd;
	int check;

	if (!(*line = (char **)malloc(sizeof(char *) * (i + 1))))
		return (error());
	(*line)[i] = NULL;
	i = 0;
	fd = open(name, O_RDONLY);
	while ((check = get_next_line(fd, &(*line)[i])) > 0)
		i++;
	close(fd);
	if (check == -1)
		return (error());
	new(lst);
	return (1);
}

void	mnoj(t_lst *l, int *x0, int *y0, int *z0)
{
	int x;
	int y;
	int z;

	x = l->matriz[0][0] * *x0 + l->matriz[0][1] * *y0 + l->matriz[0][2] * *z0;
	y = l->matriz[1][0] * *x0 + l->matriz[1][1] * *y0 + l->matriz[1][2] * *z0;
	z = l->matriz[2][0] * *x0 + l->matriz[2][1] * *y0 + l->matriz[2][2] * *z0;
	*x0 = l->matrix[0][0] * x + l->matrix[0][1] * y + l->matrix[0][2] * z;
	*y0 = l->matrix[1][0] * x + l->matrix[1][1] * y + l->matrix[1][2] * z;
	*z0 = l->matrix[2][0] * x + l->matrix[2][1] * y + l->matrix[2][2] * z;
	x = l->matriy[0][0] * *x0 + l->matriy[0][1] * *y0 + l->matriy[0][2] * *z0;
	y = l->matriy[1][0] * *x0 + l->matriy[1][1] * *y0 + l->matriy[1][2] * *z0;
	z = l->matriy[2][0] * *x0 + l->matriy[2][1] * *y0 + l->matriy[2][2] * *z0;
	z += l->per;
	*x0 = x;
	*y0 = y;
	if (l->perspective)
	{
		*x0 *= (float)(l->zp) / (float)(l->zp - z);
		*y0 *= (float)(l->zp) / (float)(l->zp - z);
	}
	*z0 = z;
}

void	nul_matrix(t_lst *lst)
{
	int i;
	int k;

	i = -1;
	while (++i < 3)
	{
		k = -1;
		while (++k < 3)
		{
			lst->matrix[i][k] = 0;
			lst->matriy[i][k] = 0;
			lst->matriz[i][k] = 0;
		}
	}
}
