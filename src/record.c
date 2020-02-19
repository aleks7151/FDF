/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   record.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabraham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 23:15:06 by vabraham          #+#    #+#             */
/*   Updated: 2019/10/29 23:15:07 by vabraham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		ft_atoi_16(char *str, int *k)
{
	int		des;

	des = 0;
	while (str[*k])
	{
		if (str[*k] == 'F' || str[*k] == 'f')
			des = des * 16 + 15;
		else if (str[*k] == 'E' || str[*k] == 'e')
			des = des * 16 + 14;
		else if (str[*k] == 'D' || str[*k] == 'd')
			des = des * 16 + 13;
		else if (str[*k] == 'C' || str[*k] == 'c')
			des = des * 16 + 12;
		else if (str[*k] == 'B' || str[*k] == 'b')
			des = des * 16 + 11;
		else if (str[*k] == 'A' || str[*k] == 'a')
			des = des * 16 + 10;
		else if (str[*k] >= '0' && str[*k] <= '9')
			des = des * 16 + str[*k] - 48;
		else
			break ;
		*k += 1;
	}
	return (des);
}

int		getsize_nbr(char *str, int i, int s)
{
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '-' && (str[i] < '0' || str[i] > '9'))
			return (error());
		if (str[i] && str[i] == '-' && (!str[i + 1]
			|| str[i + 1] < '0' || str[i + 1] > '9'))
			return (error());
		while (str[i] && str[i] == ' ')
			i++;
		if (str[i] && str[i] == '-')
			i++;
		while (str[i] && str[i] >= '0' && str[i] <= '9')
			i++;
		if (str[i] == ',')
		{
			i += 3;
			ft_atoi_16(str, &i);
		}
		if (str[i] && i != 0 && str[i] == '-')
			return (-1);
		while (str[i] && str[i] == ' ')
			i++;
		s++;
	}
	return (s);
}

void	record(t_lst *lst, int t, int k, int *ct)
{
	if (*ct <= lst->len[t])
	{
		lst->matz[t][*ct] = ft_atoi(&((lst->line)[t][k])) * lst->size_z;
		if (lst->matz[t][*ct] > lst->max_z)
			lst->max_z = lst->matz[t][*ct];
		if (lst->matz[t][*ct] < lst->min_z)
			lst->min_z = lst->matz[t][*ct];
		*ct += 1;
	}
}

void	nul_fill_out(int *cf, int nbr)
{
	int i;

	i = -1;
	while (++i < nbr)
		cf[i] = -1;
}

int		cycle(t_lst *lst, char **line)
{
	int t;
	int nbr;

	t = -1;
	while (line[++t])
	{
		nbr = getsize_nbr(line[t], 0, 0);
		if ((t != 0 && nbr != lst->len[t - 1]) || nbr < 0
			|| !(lst->matz[t] = (int *)malloc(sizeof(int) * nbr))
			|| !(lst->color_file[t] = (int *)malloc(sizeof(int) * nbr)))
			return (error());
		nul_fill_out((lst->color_file)[t], nbr);
		lst->len[t] = nbr;
	}
	if (t == 1 && nbr == 1)
		lst->data[WIDTH * HEIGHT / 2 + WIDTH / 2] = lst->color_b0;
	if (t == 1 && nbr == 1)
		lst->point = 1;
	if (WIDTH / nbr > HEIGHT / t)
		lst->a = WIDTH / nbr / 2;
	else
		lst->a = HEIGHT / t / 2;
	lst->begin_a = lst->a;
	lst->size_z = lst->a / 2;
	return (1);
}
