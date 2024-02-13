#include <fractol.h>

static void starting_values(t_complex *z, t_complex *c, t_fractal *fractal)
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

static void handle_pixel(int x, int y, t_fractal *fractal)
{
	t_complex z;
	t_complex c;
	int i = 0;

	fractal->iterations_defined = ITER;

	z.x = (rescale(x, -2, +2, 0, WIDTH) * fractal->zoom)+ fractal->shift_x; // Rescale the x number from 0 min and WIDTH max to - 2 min 2 max
	z.y = (rescale(y, 2, -2, 0, HEIGHT) * fractal->zoom) + fractal->shift_y; // Rescale the x number from 0 min and WIDTH max to - 2 min 2 max

	starting_values(&z, &c, fractal);
	fractal->escaped_value = 5;

	while (i < fractal->iterations_defined)
	{
		// z = z^2 + c
		z = sum_complex(square_complex(z), c);

		if ((z.x * z.x) + (z.y * z.y) > fractal->escaped_value)
		{
			mlx_put_pixel(fractal->img, x, y, fractal->palette[i%ITER]);
			return;
		}
		i++;
	}
	mlx_put_pixel(fractal->img, x, y, fractal->palette[0]);
}

static void handle_pixel_bur(int x, int y, t_fractal *fractal)
{
    t_complex z;
    t_complex c;
    int i = 0;
    
    fractal->iterations_defined = ITER;

	z.x = (rescale(x, -2, 2, 0, WIDTH) * fractal->zoom)+ fractal->shift_x; // Rescale the x number from 0 min and WIDTH max to - 2 min 2 max
	z.y = (rescale(y, 2, -2, 0, HEIGHT) * fractal->zoom) + fractal->shift_y; // Rescale the x number from 0 min and WIDTH max to - 2 min 2 max

	starting_values(&z, &c, fractal);
	fractal->escaped_value = 5;


	while (i < fractal->iterations_defined)
	{
        // z = abs(z)^2 + c
		z = sum_complex(square_complex_abs(z), c);

		if ((z.x * z.x) + (z.y * z.y) > fractal->escaped_value)
		{
			mlx_put_pixel(fractal->img, x, y, fractal->palette[i%ITER]);
			return;
		}
		i++;
	}
	mlx_put_pixel(fractal->img, x, y, fractal->palette[0]);
}

void fractal_render(t_fractal *fractal)
{
	int x;
	int y;

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

