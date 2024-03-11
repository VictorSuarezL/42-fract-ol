/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanz-su <vsanz-su@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:45:47 by vsanz-su          #+#    #+#             */
/*   Updated: 2024/03/11 16:53:10 by vsanz-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

void	my_keyhook(mlx_key_data_t keydata, void *param)
{
	t_fractal	*fractal;

	(void)keydata;
	fractal = (t_fractal *)param;
	if (mlx_is_key_down(fractal->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(fractal->mlx);
	if (mlx_is_key_down(fractal->mlx, MLX_KEY_LEFT))
		fractal->shift_x -= (0.5 * fractal->zoom);
	if (mlx_is_key_down(fractal->mlx, MLX_KEY_RIGHT))
		fractal->shift_x += (0.5 * fractal->zoom);
	if (mlx_is_key_down(fractal->mlx, MLX_KEY_DOWN))
		fractal->shift_y -= (0.5 * fractal->zoom);
	if (mlx_is_key_down(fractal->mlx, MLX_KEY_UP))
		fractal->shift_y += (0.5 * fractal->zoom);
	if (mlx_is_key_down(fractal->mlx, MLX_KEY_SPACE))
		shift_palette(fractal);
	fractal->render = true;
}

static void	mouse_position(t_fractal *fractal)
{
	int32_t	x;
	int32_t	y;

	mlx_get_mouse_pos(fractal->mlx, &x, &y);
	// if (x < 0)
	// 	x = 0;
	// else if (x > WIDTH)
	// 	x = WIDTH;
	// if (y < 0)
	// 	y = 0;
	// else if (y > HEIGHT)
	// 	y = HEIGHT;
	fractal->mouse_x = rescale(x, -2, 2, WIDTH);
	fractal->mouse_y = rescale(y, -2, 2, HEIGHT);
	int32_t dx;
	int32_t dy;
	dx = fractal->mouse_x - fractal->shift_x * fractal->zoom;
	dy = fractal->mouse_y - fractal->shift_y * fractal->zoom;
	fractal->shift_x += dx * fractal->zoom;
	fractal->shift_y += dy * fractal->zoom;
	printf("x = %i y = %i\nmouse_x = %i mouse_y = %i\n", x, y, fractal->mouse_x,
		fractal->mouse_y);
}

void	my_scrollhook(double xdelta, double ydelta, void *param)
{
	t_fractal	*fractal;

	(void)xdelta;
	fractal = (t_fractal *)param;
	if (ydelta > 0)
		fractal->zoom /= 1.003;
	else if (ydelta < 0)
		fractal->zoom *= 1.003;
	mouse_position(fractal);
	fractal->render = true;
}

void	close_program(void *param)
{
	t_fractal	*fractal;

	fractal = (t_fractal *)param;
	if (fractal->mlx)
	{
		mlx_close_window(fractal->mlx);
		mlx_terminate(fractal->mlx);
	}
	exit(0);
}

void	render(void *param)
{
	t_fractal	*fractal;

	fractal = (t_fractal *)param;
	if (fractal->render)
		fractal_render(fractal);
	fractal->render = false;
}
