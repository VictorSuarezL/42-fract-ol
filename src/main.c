/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanz-su <vsanz-su@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 13:24:29 by vsanz-su          #+#    #+#             */
/*   Updated: 2024/03/11 16:48:07 by vsanz-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

void	get_set(t_fractal *f, char **av, int ac)
{
	if (ft_strncmp(av[1], "Man", 3) == 0)
		f->name = "Mandelbrot";
	else if (ft_strncmp(av[1], "Jul", 3) == 0 && ac < 3)
		ft_error("->>Error: Please provide ./fractol Jul <real> <imaginary>\n");
	else if (ft_strncmp(av[1], "Jul", 3) == 0)
	{
		f->name = "Julia";
		f->julia_x = ft_atod(av[2]);
		f->julia_y = ft_atod(av[3]);
		ft_atod(av[3]);
		if (f->julia_x > 2 | f->julia_y > 2 | f->julia_y < -2 | f->julia_y < -2)
			ft_error("->>Error: Provide ./fractol Jul <real> <imaginary>\n");
	}
	else if (ft_strncmp(av[1], "Bur", 3) == 0)
		f->name = "Burning Ship";
	else
		ft_error("->>Error! Usage: ./fractol [Man | Jul | Bur]");
}

void	init(t_fractal *fractal)
{
	fractal->render = false;
	fractal->color.r_o = 9;
	fractal->color.g_o = 15;
	fractal->color.b_o = 8.5;
	fractal->shift_x = 0;
	fractal->shift_y = 0;
	fractal->zoom = 1.0;
	fractal->mouse_x = 0;
	fractal->mouse_y = 0;
	fractal->mlx = mlx_init(WIDTH, HEIGHT, fractal->name, true);
	if (!fractal->mlx)
		ft_error("fractal->mlx == NULL");
	fractal->img = mlx_new_image(fractal->mlx, WIDTH, HEIGHT);
	if (!fractal->img)
		ft_error("fractal->img == NULL");
}

int32_t	main(int ac, char *av[])
{
	t_fractal	fractal;

	if (ac < 2)
		ft_error("->>Error! Usage: ./fractol [Man | Jul | Bur]");
	get_set(&fractal, av, ac);
	init(&fractal);
	init_color_palette(&fractal);
	fractal_render(&fractal);
	mlx_key_hook(fractal.mlx, &my_keyhook, &fractal);
	mlx_scroll_hook(fractal.mlx, &my_scrollhook, &fractal);
	mlx_close_hook(fractal.mlx, &close_program, &fractal);
	if (mlx_image_to_window(fractal.mlx, fractal.img, 0, 0) < 0)
		ft_error("Error image to window!");
	mlx_loop_hook(fractal.mlx, &render, &fractal);
	mlx_loop(fractal.mlx);
	mlx_terminate(fractal.mlx);
	return (EXIT_SUCCESS);
}
