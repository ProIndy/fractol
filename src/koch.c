/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   koch.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaaskel <ijaaskel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 13:13:13 by ijaaskel          #+#    #+#             */
/*   Updated: 2023/01/26 13:14:11 by ijaaskel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	reset_koch(t_data *data)
{
	data->max_iter = KOCH_ITER;
	data->kdata.zoom = 1.0;
	data->kdata.x_off = 400.0;
	data->kdata.y_off = 300.0;
	data->kdata.d_iter = (double)data->max_iter;
	data->kdata.n_iter = 0;
}

void	move_koch(int key, t_data *data)
{
	if (key == 123 || key == 65361)
		data->kdata.x_off += 50 * sqrt(data->kdata.zoom);
	if (key == 124 || key == 65363)
		data->kdata.x_off -= 50 * sqrt(data->kdata.zoom);
	if (key == 126 || key == 65362)
		data->kdata.y_off += 50 * sqrt(data->kdata.zoom);
	if (key == 125 || key == 65364)
		data->kdata.y_off -= 50 * sqrt(data->kdata.zoom);
}

void	init_koch(t_data *data)
{
	t_kdata	kdata;

	data->max_iter = KOCH_ITER;
	kdata.zoom = 1.0;
	kdata.x_off = 400.0;
	kdata.y_off = 300.0;
	kdata.d_iter = (double)data->max_iter;
	data->kdata.n_iter = 0;
	data->kdata = kdata;
}

static void	grow(t_point p[2], t_loop_counter a, t_data *data, int n)
{
	t_point	t[3];

	t[0].x = (2 * p[0].x + p[1].x) / 3;
	t[0].y = (2 * p[0].y + p[1].y) / 3;
	t[1].x = (p[0].x + 2 * p[1].x) / 3;
	t[1].y = (p[0].y + 2 * p[1].y) / 3;
	t[2].x = t[0].x + (t[1].x - t[0].x) * cos(a.angle) + (t[1].y - t[0].y) * \
		sin(a.angle);
	t[2].y = t[0].y + (t[1].x - t[0].x) * -sin(a.angle) + (t[1].y - t[0].y) * \
		cos(a.angle);
	if (n == 0)
		draw_line(data, &p[0], &p[1], a.counter);
	else
	{
		grow((t_point[2]){p[0], t[0]}, a, data, n - 1);
		a.counter++;
		grow((t_point[2]){t[0], t[2]}, a, data, n - 1);
		grow((t_point[2]){t[2], t[1]}, a, data, n - 1);
		a.counter--;
		grow((t_point[2]){t[1], p[1]}, a, data, n - 1);
	}
}

void	koch(t_data *data)
{
	t_point			p[3];
	t_loop_counter	a;

	clear_image(data);
	a.angle = 60 * M_PI / 180;
	a.counter = 0;
	p[0].x = -200 * data->kdata.zoom + data->kdata.x_off;
	p[0].y = -100 * data->kdata.zoom + data->kdata.y_off;
	p[1].x = 200 * data->kdata.zoom + data->kdata.x_off;
	p[1].y = -100 * data->kdata.zoom + data->kdata.y_off;
	p[2].x = p[0].x + (p[1].x - p[0].x) / 2;
	p[2].y = p[0].y + sqrt(pow((p[1].x - p[0].x), 2) - \
			pow((p[1].x - p[0].x), 2) / 2);
	grow((t_point[2]){p[0], p[1]}, a, data, data->max_iter);
	grow((t_point[2]){p[1], p[2]}, a, data, data->max_iter);
	grow((t_point[2]){p[2], p[0]}, a, data, data->max_iter);
}
