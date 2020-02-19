/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabraham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 22:19:53 by vabraham          #+#    #+#             */
/*   Updated: 2019/10/11 23:40:00 by vabraham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	abc(int x, int y)
{
	if (x >= y)
		return ((float)(x - y));
	return ((float)(y - x));
}

int		get_color(t_color cl, int min, int max, int cur)
{
	float	perc;
	int		red;
	int		green;
	int		blue;

	cl.cb = cl.color0;
	cl.ce = cl.color1;
	if (max - min == 0)
		perc = 0;
	else
		perc = (float)(cur - min) / (float)(max - min);
	red = (int)((1 - perc) * (cl.cb >> 16) + perc * (cl.ce >> 16));
	green = (int)((1 - perc) * ((cl.cb >> 8) & 0xFF)
		+ perc * ((cl.ce >> 8) & 0xFF));
	blue = (int)((1 - perc) * (cl.cb & 0xFF) + perc * (cl.ce & 0xFF));
	return (red << 16 | green << 8 | blue);
}

void	fon(int *data, int col)
{
	int i;

	i = -1;
	while (++i < WIDTH * HEIGHT)
		data[i] = col;
}

int		main(int argc, char **argv)
{
	int		fd;
	t_lst	*lst;

	if (argc != 2)
		return (ussage());
	lst = malloc(sizeof(t_lst));
	lst->mlx_ptr = mlx_init();
	lst->win_ptr = mlx_new_window(lst->mlx_ptr, WIDTH, HEIGHT, "FDF");
	lst->img_ptr = mlx_new_image(lst->mlx_ptr, WIDTH, HEIGHT);
	lst->data = (int *)mlx_get_data_addr(lst->img_ptr,
		&(lst->n0), &(lst->n1), &(lst->n2));
	if ((fd = open(argv[1], O_RDONLY)) <= 0)
		return (error());
	lst->i = 0;
	while (get_next_line(fd, &(lst->str)) > 0)
	{
		(lst->i)++;
		free(lst->str);
	}
	close(fd);
	mlx_hook(lst->win_ptr, 2, 0, kp, (void *)lst);
	fill_in(lst, &(lst->line), lst->i, argv[1]);
	mlx_put_image_to_window(lst->mlx_ptr, lst->win_ptr, lst->img_ptr, 0, 0);
	mlx_loop(lst->mlx_ptr);
	return (0);
}
