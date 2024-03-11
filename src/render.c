/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanz-su <vsanz-su@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 13:24:10 by vsanz-su          #+#    #+#             */
/*   Updated: 2024/03/11 14:04:41 by vsanz-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

static void	starting_values(t_complex *z, t_complex *c, t_fractal *fractal)
{
	if (!ft_strncmp(fractal->name, "Julia", 5))
	{
		c->x = fractal->julia_x;
		c->y = fractal->julia_y;
	}
	else
	{
		c->x = z->x;
		c->y = z->y;
	}
}

static void	handle_pixel(int x, int y, t_fractal *fractal)
{
	t_complex	z;
	t_complex	c;
	int			i;

	i = 0;
	fractal->iterations_defined = ITER;
	z.x = (rescale(x, -2, +2, WIDTH) * fractal->zoom) + fractal->shift_x;
	z.y = (rescale(y, 2, -2, HEIGHT) * fractal->zoom) + fractal->shift_y;
	starting_values(&z, &c, fractal);
	fractal->escaped_value = 5;
	while (i < fractal->iterations_defined)
	{
		z = sum_complex(square_complex(z), c);
		if ((z.x * z.x) + (z.y * z.y) > fractal->escaped_value)
		{
			mlx_put_pixel(fractal->img, x, y, fractal->palette[i % ITER]);
			return ;
		}
		i++;
	}
	mlx_put_pixel(fractal->img, x, y, RED);
}

static void	handle_pixel_bur(int x, int y, t_fractal *fractal)
{
	t_complex	z;
	t_complex	c;
	int			i;

	i = 0;
	fractal->iterations_defined = ITER;
	z.x = (rescale(x, -2, 2, WIDTH) * fractal->zoom) + fractal->shift_x;
	z.y = (rescale(y, -2, 2, HEIGHT) * fractal->zoom) + fractal->shift_y;
	starting_values(&z, &c, fractal);
	fractal->escaped_value = 5;
	while (i < fractal->iterations_defined)
	{
		z = sum_complex(square_complex_abs(z), c);
		if ((z.x * z.x) + (z.y * z.y) > fractal->escaped_value)
		{
			mlx_put_pixel(fractal->img, x, y, fractal->palette[i % ITER]);
			return ;
		}
		i++;
	}
	mlx_put_pixel(fractal->img, x, y, RED);
}

void	fractal_render(t_fractal *fractal)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < (HEIGHT))
	{
		x = 0;
		while (x < WIDTH)
		{
			if (ft_strncmp(fractal->name, "Burning Ship", 3) == 0)
			{
				handle_pixel_bur(x, y, fractal);
			}
			else
			{
				handle_pixel(x, y, fractal);
			}
			x++;
		}
		y++;
	}
}
