/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaaskel <ijaaskel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 12:42:52 by ijaaskel          #+#    #+#             */
/*   Updated: 2023/01/26 13:06:39 by ijaaskel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

static void	move(int key, t_data *data)
{
	if (key == 123 || key == 65361)
	{
		data->min_x -= data->x_factor * 100.0;
		data->max_x -= data->x_factor * 100.0;
	}
	if (key == 124 || key == 65363)
	{
		data->min_x += data->x_factor * 100.0;
		data->max_x += data->x_factor * 100.0;
	}
	if (key == 126 || key == 65362)
	{
		data->min_y += data->y_factor * 75.0;
		data->max_y = (data->min_y + (data->max_x - data->min_x)) * \
			W_HEIGHT / W_WIDTH;
	}
	if (key == 125 || key == 65364)
	{
		data->min_y -= data->y_factor * 75.0;
		data->max_y = (data->min_y + (data->max_x - data->min_x)) * \
			W_HEIGHT / W_WIDTH;
	}
}

int	manage_keys(int key, t_data *data)
{
	if (key == 53 || key == 0xff1b)
		fractol_exit(data);
	else if ((key >= 123 && key <= 126) || (key >= 65361 && key <= 65364))
	{
		if (data->type != 3)
			move(key, data);
		else
			move_koch(key, data);
	}
	else if ((key == 43 || key == 69 || key == 45 || key == 78))
	{
		if (data->type == 3)
			koch_key_zoom(key, data);
		else if (key == 43 || key == 69)
			zoom_in(data, 400, 300);
		else if (key == 45 || key == 78)
			zoom_out(data, 400, 300);
	}
	else if ((key == 15 || key == 114) && data->type == 3)
		reset_koch(data);
	fractol(data);
	return (0);
}

int	manage_mouse(int key, int x, int y, t_data *data)
{
	if (data->type != 3)
	{
		if (key == 4)
			zoom_in(data, x, y);
		if (key == 5)
			zoom_out(data, x, y);
	}
	else
	{
		if (key == 4)
			zoom_in_koch(data, 400, 300);
		if (key == 5)
			zoom_out_koch(data, 400, 300);
	}
	mlx_clear_window(data->mlx, data->win);
	fractol(data);
	return (0);
}

int	manage_pointer(int x, int y, t_data *data)
{
	if (data->type == 1)
	{
		data->mouse_x = x * 3.5 / W_WIDTH - 1.75;
		data->mouse_y = y * 2.0 / W_HEIGHT - 1.0;
		fractol(data);
	}
	return (0);
}
