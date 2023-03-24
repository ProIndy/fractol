/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaaskel <ijaaskel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 13:00:52 by ijaaskel          #+#    #+#             */
/*   Updated: 2023/01/26 13:01:27 by ijaaskel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <mlx.h>
# include <math.h>
# include "../libft/includes/libft.h"

# define W_WIDTH 800
# define W_HEIGHT 600

# define ITER 100
# define KOCH_ITER 3

typedef struct s_img
{
	void	*img;
	void	*add;
	int		bpp;
	int		x_len;
	int		endian;
}			t_img;

typedef struct s_kdata
{
	double	zoom;
	double	x_off;
	double	y_off;
	double	d_iter;
	int		n_iter;
}			t_kdata;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	t_img		img;
	int			type;
	long double	min_x;
	long double	max_x;
	long double	min_y;
	long double	max_y;
	long double	x_factor;
	long double	y_factor;
	double		c_x;
	double		c_y;
	double		z_x;
	double		z_x2;
	double		z_y;
	double		z_y2;
	double		mouse_x;
	double		mouse_y;
	long		max_iter;
	double		f_iter;
	int			color_r;
	int			color_g;
	int			color_b;
	t_kdata		kdata;
}				t_data;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_line
{
	int	x0;
	int	y0;
	int	x1;
	int	y1;
	int	dx;
	int	dy;
}		t_line;

typedef struct s_loop_counter
{
	double	angle;
	int		counter;
}			t_loop_counter;

void	clear_image(t_data *data);
void	pixel_put_to_image(t_data *data, int x, int y, int n);
void	fractol(t_data *data);
void	julia(t_data *data, int x, int y, int n);
void	init_koch(t_data *data);
void	zoom_in_koch(t_data *data, int x, int y);
void	zoom_out_koch(t_data *data, int x, int y);
void	move_koch(int key, t_data *data);
void	koch_key_zoom(int key, t_data *data);
void	koch(t_data *data);
void	reset_koch(t_data *data);
void	mandelbrot(t_data *data, int x, int y, int n);
int		manage_keys(int key, t_data *data);
int		manage_mouse(int key, int x, int y, t_data *data);
void	zoom_in(t_data *data, int x, int y);
void	zoom_out(t_data *data, int x, int y);
int		manage_pointer(int x, int y, t_data *data);
void	draw_line(t_data *data, t_point *start, t_point *end, int n);
void	fractol_error(char *output, t_data *data);
void	fractol_exit(t_data *data);

#endif
