/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaaskel <ijaaskel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 13:15:52 by ijaaskel          #+#    #+#             */
/*   Updated: 2023/01/26 13:16:22 by ijaaskel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	mandelbrot(t_data *data, int x, int y, int n)
{
	double	temp;

	while (data->z_x * data->z_x + data->z_y * data->z_y <= 4 && \
			n < data->max_iter)
	{
		temp = (data->z_x * data->z_x) - (data->z_y * data->z_y);
		data->z_y = (2 * data->z_x * data->z_y) + data->c_y;
		data->z_x = temp + data->c_x;
		n++;
	}
	pixel_put_to_image(data, x, y, n);
}
