/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaaskel <ijaaskel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 12:43:02 by ijaaskel          #+#    #+#             */
/*   Updated: 2023/01/22 13:32:09 by ijaaskel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

static int	get_fractal_type(char *type)
{
	int	fractal_type;

	if (!ft_strcmp(type, "julia"))
		fractal_type = 1;
	else if (!ft_strcmp(type, "mandelbrot"))
		fractal_type = 2;
	else if (!ft_strcmp(type, "koch"))
		fractal_type = 3;
	else
	{
		fractal_type = 0;
		fractol_error("Usage: ./fractol [fractal]\n\nFractals: \
		\n\tjulia\n\tmandelbrot\n\tkoch\n", NULL);
	}
	return (fractal_type);
}

static void	set_window_dimensions(t_data *data)
{
	data->min_x = -2.0;
	data->max_x = 2.0;
	data->min_y = -1.5;
	data->max_y = (data->min_y + (data->max_x - data->min_x)) * \
		W_HEIGHT / W_WIDTH;
	data->x_factor = (data->max_x - data->min_x) / (W_WIDTH - 1);
	data->y_factor = (data->max_y - data->min_y) / (W_HEIGHT - 1);
}

static t_data	init_everything(char *type)
{
	t_data	data;

	data.type = get_fractal_type(type);
	data.mlx = mlx_init();
	if (!data.mlx)
		fractol_error("error: could not initialize mlx\n", &data);
	data.win = mlx_new_window(data.mlx, W_WIDTH, W_HEIGHT, "Fractol");
	if (!data.win)
		fractol_error("error: could not create window\n", &data);
	data.img.img = mlx_new_image(data.mlx, W_WIDTH, W_HEIGHT);
	if (!data.img.img)
		fractol_error("error: could not create image\n", &data);
	data.img.add = mlx_get_data_addr(data.img.img, &data.img.bpp, \
		&data.img.x_len, &data.img.endian);
	if (!data.img.add)
		fractol_error("error: could not set up the image\n", &data);
	set_window_dimensions(&data);
	data.max_iter = ITER;
	data.f_iter = (double)data.max_iter;
	data.mouse_x = -0.6475;
	data.mouse_y = -0.43;
	data.color_r = 0x50;
	data.color_g = 0x20;
	data.color_b = 0x30;
	return (data);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac > 2)
		fractol_error("Usage: ./fractol [fractal set] \
			\n\nPlease, enter only one fractal set\n", NULL);
	else if (ac != 2)
		fractol_error("Usage: ./fractol [fractal set]\n\nFractal sets: \
			\n\tjulia\n\tmandelbrot\n\tkoch\n", NULL);
	data = init_everything(av[1]);
	if (data.type == 3)
		init_koch(&data);
	mlx_clear_window(data.mlx, data.win);
	fractol(&data);
	mlx_key_hook(data.win, manage_keys, &data);
	mlx_mouse_hook(data.win, manage_mouse, &data);
	if (data.type == 1)
		mlx_hook(data.win, 6, 1L << 6, manage_pointer, &data);
	mlx_loop(data.mlx);
}
