/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaaskel <ijaaskel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 12:43:10 by ijaaskel          #+#    #+#             */
/*   Updated: 2023/01/26 13:03:40 by ijaaskel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

static void	add_instructions(t_data *data)
{
	mlx_string_put(data->mlx, data->win, 20, 20, 0xFFFFFF, "Move: Arrows");
	mlx_string_put(data->mlx, data->win, 20, 40, 0xFFFFFF, "Zoom: Mouse wheel");
	mlx_string_put(data->mlx, data->win, 20, 60, 0xFFFFFF, "Zoom: +/-");
	mlx_string_put(data->mlx, data->win, 20, 80, 0xFFFFFF, "(Koch) Reset: R");
	mlx_string_put(data->mlx, data->win, 20, 100, 0xFFFFFF, "Exit: Esc");
}

static void	calc_function(t_data *data, int x, int y)
{
	if (data->type == 1)
		julia(data, x, y, 0);
	else if (data->type == 2)
		mandelbrot(data, x, y, 0);
	else
		fractol_error("error: something went wrong", data);
}

void	fractol(t_data *data)
{
	unsigned int	x;
	unsigned int	y;

	y = 0;
	if (data->type == 3)
		koch(data);
	else
	{
		while (++y < W_HEIGHT)
		{
			x = 0;
			while (++x < W_WIDTH)
			{
				data->c_y = data->max_y - (y * data->y_factor);
				data->c_x = data->min_x + (x * data->x_factor);
				data->z_x = data->c_x;
				data->z_y = data->c_y;
				calc_function(data, x, y);
			}
		}
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	add_instructions(data);
}
