/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaaskel <ijaaskel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 13:16:40 by ijaaskel          #+#    #+#             */
/*   Updated: 2023/01/26 13:16:41 by ijaaskel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	zoom_in(t_data *data, int x, int y)
{
	double	ratio;

	if (data->max_iter < 10000000)
	{
		ratio = ((double)x / (double)W_WIDTH);
		data->min_x += data->x_factor * 100.0 * ratio;
		data->max_x -= data->x_factor * 100.0 * (1.0 - ratio);
		ratio = ((double)y / (double)W_HEIGHT);
		data->min_y += data->y_factor * 75.0 * (1.0 - ratio);
		data->max_y -= data->y_factor * 75.0 * ratio;
		data->x_factor = (data->max_x - data->min_x) / (W_WIDTH - 1);
		data->y_factor = (data->max_y - data->min_y) / (W_HEIGHT - 1);
		data->f_iter *= 1.045;
		data->max_iter = (int)data->f_iter;
	}
}

void	zoom_out(t_data *data, int x, int y)
{
	double	ratio;

	if (data->max_iter > 40)
	{
		ratio = ((double)x / (double)W_WIDTH);
		data->min_x -= data->x_factor * 100.0 * ratio;
		data->max_x += data->x_factor * 100.0 * (1.0 - ratio);
		ratio = ((double)y / (double)W_HEIGHT);
		data->min_y -= data->y_factor * 75.0 * (1.0 - ratio);
		data->max_y += data->y_factor * 75.0 * ratio;
		data->x_factor = (data->max_x - data->min_x) / (W_WIDTH - 1);
		data->y_factor = (data->max_y - data->min_y) / (W_HEIGHT - 1);
		data->f_iter /= 1.043;
		data->max_iter = (int)data->f_iter;
	}
}

void	zoom_in_koch(t_data *data, int x, int y)
{
	double	ratio;

	if (y >= 0 && y <= W_HEIGHT && x >= 0 && x <= W_WIDTH)
	{
		ratio = ((double)x / (double)W_WIDTH);
		data->kdata.x_off += (1 - (ratio * 2)) * 400 * data->kdata.zoom;
		ratio = ((double)y / (double)W_HEIGHT);
		data->kdata.y_off += (1 - (ratio * 2)) * 300 * data->kdata.zoom;
		data->kdata.zoom *= 1.2;
		if (data->kdata.d_iter < 15.0)
			data->kdata.d_iter *= 1 + (1 / (4 * data->kdata.d_iter));
		else
			data->kdata.d_iter = 15.0;
		data->max_iter = (int)data->kdata.d_iter;
	}
}

void	zoom_out_koch(t_data *data, int x, int y)
{
	double	ratio;
	double	temp;

	if (y >= 0 && y <= W_HEIGHT && x >= 0 && x <= W_WIDTH)
	{
		ratio = ((double)x / (double)W_WIDTH);
		data->kdata.x_off -= (1 - (ratio * 2)) * 400 * data->kdata.zoom;
		ratio = ((double)y / (double)W_HEIGHT);
		data->kdata.y_off -= (1 - (ratio * 2)) * 300 * data->kdata.zoom;
		temp = data->kdata.zoom / 1.2;
		data->kdata.d_iter /= 1 + (1 / (4 * data->kdata.d_iter));
		if (temp > 1)
		{
			data->kdata.zoom /= 1.2;
			data->max_iter = (int)data->kdata.d_iter;
		}
		else
		{
			data->kdata.zoom = 1.0;
			data->kdata.d_iter = (double)KOCH_ITER;
			data->max_iter = (int)data->kdata.d_iter;
		}
	}
}

void	koch_key_zoom(int key, t_data *data)
{
	if (key == 43 || key == 69)
	{
		zoom_in_koch(data, 400, 300);
	}
	else if (key == 45 || key == 78)
	{
		zoom_out_koch(data, 400, 300);
	}
}
