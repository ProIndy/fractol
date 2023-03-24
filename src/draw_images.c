/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaaskel <ijaaskel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 13:01:53 by ijaaskel          #+#    #+#             */
/*   Updated: 2023/01/26 13:02:36 by ijaaskel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	clear_image(t_data *data)
{
	int	row;
	int	col;
	int	*pxl;

	row = 0;
	while (row < W_HEIGHT)
	{
		col = 0;
		while (col < W_WIDTH)
		{
			pxl = data->img.add + (row * data->img.x_len + col * \
					(data->img.bpp / 8));
			if (data->type != 3)
				*pxl = 0x000000;
			else
				*pxl = 0x000000;
			col++;
		}
		row++;
	}
}

void	pixel_put_to_image(t_data *data, int x, int y, int n)
{
	int	*pxl;

	if (x >= 0 && x < W_WIDTH && y >= 0 && y < W_HEIGHT && n == data->max_iter)
	{
		pxl = data->img.add + (y * data->img.x_len + x * (data->img.bpp / 8));
		*pxl = 0xFFFFFF;
	}
	else if (x >= 0 && x < W_WIDTH && y >= 0 && y < W_HEIGHT)
	{
		pxl = data->img.add + (y * data->img.x_len + x * (data->img.bpp / 8));
		*pxl = data->color_r + (n * 2);
		pxl = data->img.add + (y * data->img.x_len + x * \
				(data->img.bpp / 8) + 1);
		*pxl = data->color_g + (n * 3);
		pxl = data->img.add + (y * data->img.x_len + x * \
				(data->img.bpp / 8) + 2);
		*pxl = data->color_b + (n * 4);
	}
}
