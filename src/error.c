/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaaskel <ijaaskel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 12:42:46 by ijaaskel          #+#    #+#             */
/*   Updated: 2023/01/22 13:31:16 by ijaaskel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	fractol_error(char *output, t_data *data)
{
	ft_putstr_fd(output, 2);
	if (data)
	{
		if (data->mlx && data->img.img)
			mlx_destroy_image(data->mlx, data->img.img);
		if (data->mlx && data->win)
			mlx_destroy_window(data->mlx, data->win);
	}
	exit (0);
}

void	fractol_exit(t_data *data)
{
	if (data)
	{
		if (data->mlx && data->img.img)
			mlx_destroy_image(data->mlx, data->img.img);
		if (data->mlx && data->win)
			mlx_destroy_window(data->mlx, data->win);
	}
	exit (0);
}
