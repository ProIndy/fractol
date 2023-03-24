/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaaskel <ijaaskel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 13:12:25 by ijaaskel          #+#    #+#             */
/*   Updated: 2023/01/26 13:13:00 by ijaaskel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	julia(t_data *data, int x, int y, int n)
{
	double	temp;

	data->c_x = data->mouse_x;
	data->c_y = data->mouse_y;
	while (data->z_x * data->z_x + data->z_y * data->z_y <= 4 && \
			n < data->max_iter)
	{
		temp = (data->z_x * data->z_x) - (data->z_y * data->z_y);
		data->z_y = (2 * data->z_x * data->z_y) - data->c_y;
		data->z_x = temp + data->c_x;
		n++;
	}
	pixel_put_to_image(data, x, y, n);
}
