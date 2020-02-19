/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabraham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 17:23:10 by vabraham          #+#    #+#             */
/*   Updated: 2019/10/31 16:15:43 by vabraham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define WIDTH 2500
# define HEIGHT 1200
# define FON 0x444488
# define BLUE 0x00FFFF
# define RED 0xFFFF00//FF4488
# define FON0 0x4B0082
# define GREEN 0x00FF00
# define YELLOW 0xCC6600
# define COLOR_B 0x00FFFF
# define COLOR_E 0xFF4488
# define SH_X WIDTH / 2 + 100
# define SH_Y HEIGHT / 2 + 100
# include "mlx.h"
# include "../includes/libft/get_next_line.h"
# include <math.h>

typedef struct		s_lst
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	char			**line;
	int				*data;
	int				i;
	int				a;
	int				begin_a;
	int				size_z;
	float			al_x;
	float			al_y;
	float			al_z;
	int				per;
	float			matrix[3][3];
	float			matriy[3][3];
	float			matriz[3][3];
	int				*len;
	int				**matz;
	int				**color_file;
	int				x0;
	int				y0;
	int				z0;
	int				z0_begin;
	int				color0;
	int				x1;
	int				y1;
	int				z1;
	int				z1_begin;
	int				color1;
	int				x2;
	int				y2;
	int				z2;
	int				z2_begin;
	int				color2;
	int				n0;
	int				n1;
	int				n2;
	int				min_z;
	int				max_z;
	int				color_b;
	int				color_b0;
	int				color_e;
	int				color_e0;
	int				color_fon;
	char			*str;
	int				check_xy;
	int				get_color;
	int				perspective;
	int				zp;
	int				point;
}					t_lst;

typedef struct		s_llst
{
	float			len;
	int				z1;
	int				z2;
	int				x;
	int				y;
}					t_draw;

typedef struct		s_lllist
{
	int				color0;
	int				color1;
	float			er;
	int				opt;
	int				yn;
	int				xn;
	int				cb;
	int				ce;
}					t_color;

int					fill_in(t_lst *lst, char ***line, int i, char *name);
int					new(t_lst *lst);
void				draw_line(t_lst lst);
void				home(t_lst *lst);
void				new_0(t_lst *lst, int t, int k);
int					error(void);
int					ussage(void);
void				fon(int *data, int col);
int					kp(int key, void *l);
void				mnoj(t_lst *l, int *x0, int *y0, int *z0);
void				record(t_lst *lst, int t, int k, int *ct);
int					ft_atoi_16(char *str, int *k);
int					cycle(t_lst *lst, char **line);
void				nul_matrix(t_lst *lst);
float				abc(int x, int y);
int					get_color(t_color cl, int min, int max, int cur);
int					check_color(char *str, int *k);

#endif
