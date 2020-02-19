/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabraham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 23:07:27 by vabraham          #+#    #+#             */
/*   Updated: 2019/10/29 23:07:29 by vabraham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		kp_2(int key, t_lst *lst)
{
	if (key == 43)
	{
		lst->color_b0 = GREEN;
		lst->color_e0 = YELLOW;
		lst->color_fon = FON0;
	}
	else if (key == 47)
	{
		lst->color_b0 = BLUE;
		lst->color_e0 = RED;
		lst->color_fon = FON;
	}
	fon(lst->data, lst->color_fon);
	home(lst);
	mlx_put_image_to_window(lst->mlx_ptr, lst->win_ptr, lst->img_ptr, 0, 0);
	return (0);
}

int		kp_1(int key, t_lst *lst)
{
	if (key == 45)
	{
		lst->al_x = 0;
		lst->al_y = 0;
		lst->al_z = 0;
		lst->per = 0;
		lst->perspective = 0;
	}
	else if (key == 24)
	{
		lst->a *= 2;
		lst->size_z *= 2;
		new_0(lst, -1, 0);
	}
	else if (key == 27 && lst->a > lst->begin_a / 4)
	{
		lst->a /= 2;
		lst->size_z /= 2;
		new_0(lst, -1, 0);
	}
	else if (key == 6 && lst->perspective)
		lst->zp += 100;
	else if (key == 7 && lst->zp - 100 > 0 && lst->perspective)
		lst->zp -= 100;
	return (kp_2(key, lst));
}

int		kp_0(int key, t_lst *lst)
{
	if (key == 1 && lst->perspective)
		lst->per += 10;
	else if (key == 2 && lst->perspective)
		lst->per += 100;
	else if (key == 35)
	{
		if (lst->perspective == 0)
			lst->perspective = 1;
		else
			lst->perspective = 0;
		lst->per = 0;
	}
	else if (key == 11)
	{
		lst->al_x = 27 * 0.04;
		lst->al_y = 0;
		lst->al_z = -27 * 0.04;
		lst->per = 0;
		lst->perspective = 0;
	}
	return (kp_1(key, lst));
}

int		kp(int key, void *l)
{
	t_lst	*lst;

	lst = (t_lst *)l;
	if (key == 53)
		exit(0);
	if (lst->point)
		return (0);
	if (key == 126)
		lst->al_x += 0.04;
	else if (key == 125)
		lst->al_x -= 0.04;
	else if (key == 123)
		lst->al_y -= 0.04;
	else if (key == 124)
		lst->al_y += 0.04;
	else if (key == 30)
		lst->al_z += 0.04;
	else if (key == 33)
		lst->al_z -= 0.04;
	else if (key == 13 && lst->perspective)
		lst->per -= 10;
	else if (key == 14 && lst->perspective)
		lst->per -= 100;
	return (kp_0(key, lst));
}

int		check_color(char *str, int *k)
{
	if (str[*k + 1] != '0')
		return (error());
	if (str[*k + 2] != 'x')
		return (error());
	*k += 3;
	return (1);
}
