/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaaskel <ijaaskel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 13:03:10 by ijaaskel          #+#    #+#             */
/*   Updated: 2023/01/26 13:03:11 by ijaaskel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

static void	koch_pixel_put_to_image(t_data *data, int x, int y, int n)
{
	int	*pxl;

	if (x > 0 && x < W_WIDTH - 1 && y > 0 && y < W_HEIGHT - 1)
	{
		pxl = data->img.add + (y * data->img.x_len + x * (data->img.bpp / 8));
		*pxl = 0xffff00 - (n * 0x003000);
		pxl = data->img.add + ((y - 1) * data->img.x_len + x * \
			(data->img.bpp / 8));
		*pxl = 0xffff00 - (n * 0x003000);
		pxl = data->img.add + ((y + 1) * data->img.x_len + x * \
			(data->img.bpp / 8));
		*pxl = 0xffff00 - (n * 0x003000);
		pxl = data->img.add + (y * data->img.x_len + (x - 1) * \
			(data->img.bpp / 8));
		*pxl = 0xffff00 - (n * 0x003000);
		pxl = data->img.add + (y * data->img.x_len + (x + 1) * \
			(data->img.bpp / 8));
		*pxl = 0xffff00 - (n * 0x003000);
	}
}

static void	draw_down(t_data *data, t_line line, int x, int n)
{
	int	y;

	if (line.dy < 0)
	{
		y = line.y1;
		while (y++ <= line.y0)
			koch_pixel_put_to_image(data, x, y, n);
	}
	else if (line.dy > 0)
	{
		y = line.y0;
		while (y++ <= line.y1)
			koch_pixel_put_to_image(data, x, y, n);
	}
	else
	{
		y = line.y0;
		koch_pixel_put_to_image(data, x, y, n);
	}
}

static void	draw_points_to_line(t_data *data, t_line line, int x, int n)
{
	int	y;

	y = (((line.dy * (x - line.x0)) / line.dx) + line.y0);
	koch_pixel_put_to_image(data, x, y, n);
}

static t_line	set_line(t_point *start, t_point *end)
{
	t_line	line;

	line.x0 = start->x;
	line.y0 = start->y;
	line.x1 = end->x;
	line.y1 = end->y;
	line.dx = line.x1 - line.x0;
	line.dy = line.y1 - line.y0;
	return (line);
}

void	draw_line(t_data *data, t_point *start, t_point *end, int n)
{
	t_line	line;
	int		x;

	line = set_line(start, end);
	x = 0;
	if (line.x0 < line.x1)
	{
		while (x++ < W_WIDTH)
		{
			if (x >= line.x0 && x <= line.x1)
				draw_points_to_line(data, line, x, n);
		}
	}
	else if (line.x0 > line.x1)
	{
		while (x++ < W_WIDTH)
		{
			if (x <= line.x0 && x >= line.x1)
				draw_points_to_line(data, line, x, n);
		}
	}
	else
		draw_down(data, line, line.x0, n);
}
