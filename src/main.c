
#include <fractol.h>

static void error(void)
{
	puts(mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

void get_set(t_fractal *f, char **av, int ac)
{
	if (ft_strncmp(av[1], "Man", 3) == 0)
		f->name = "Mandelbrot";
	else if (ft_strncmp(av[1], "Jul", 3) == 0 && ac < 3)
		ft_error("->>Error: Please specify the type of fractal to display.\n->>Usage: ./fractal_program [Mandelbrot | Julia]");
	else if (ft_strncmp(av[1], "Jul", 3) == 0)
	{
		// init_julia(f, av);
		f->name = "Julia";
		f->julia_x = ft_atod(av[2]);
		f->julia_y = ft_atod(av[3]);
		if(f->julia_x > 2 | f->julia_y > 2 | f->julia_y < -2 | f->julia_y < -2)
			ft_error("->>Error: Incorrect parameters for Julia fractal.\n->>Please provide valid parameters in the format:\n\t./fractal_program Julia <real> <imaginary>");
	}
	else
		ft_error("->>Error: Please specify the type of fractal to display.\n->>Usage: ./fractal_program [Mandelbrot | Julia]");
}

void starting_values(t_complex *z, t_complex *c, t_fractal *fractal)
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

void handle_pixel(int x, int y, t_fractal *fractal)
{
	t_complex z;
	t_complex c;
	int i = 0;

	fractal->iterations_defined = ITER;

	z.x = (rescale(x, -2, +2, 0, WIDTH) * fractal->zoom)+ fractal->shift_x + fractal->mouse_x; // Rescale the x number from 0 min and WIDTH max to - 2 min 2 max
	z.y = (rescale(y, 2, -2, 0, HEIGHT) * fractal->zoom) + fractal->shift_y + fractal->mouse_y; // Rescale the x number from 0 min and WIDTH max to - 2 min 2 max

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
			handle_pixel(x, y, fractal);
			x++;
		}
		y++;
	}
}

void init_color_palette(t_fractal *data)
{
	int		i;
	double	t;
	int		r;
	int		g;
	int		b;

	i = 1;
	data->palette[0] = DEEP_SKY_BLUE;


	while (i < ITER)
	{
		t = (double)i / (ITER / 2);
		r = (int)(data->color.r_o * (1 - t) * t * t * t * 255);
		g = (int)(data->color.g_o * (1 - t) * (1 - t) * t * t * 255);
		b = (int)(data->color.b_o * (1 - t) * (1 - t) * (1 - t) * t * 255);
		data->palette[i] = (r << 24) | (g << 16) | (b << 8) | 255;
		i++;
	}
}

void shift_palette(t_fractal *fractal)
{
	fractal->color.r_o += 0.5;
	fractal->color.g_o += 0.5;
	fractal->color.b_o += 0.5;

	init_color_palette(fractal);
}

void my_keyhook(mlx_key_data_t keydata, void *param)
{
	t_fractal *fractal;

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
	fractal->render=true;
}

void render(void *param)
{
	t_fractal *fractal;

	fractal = (t_fractal *)param;

	if(fractal->render)
		fractal_render(fractal);
	fractal->render = false;
}

void mouse_position(t_fractal *fractal)
{
	int32_t x;
	int32_t y;

	mlx_get_mouse_pos(fractal->mlx, &x, &y);
	if(x < 0)
		x = 0;
	else if (x > WIDTH)
	{
		x = WIDTH;
	}
	if (y < 0)
	{
		y = 0;
	}
	else if (y > HEIGHT)
	{
		y = HEIGHT;
	}

	fractal->mouse_x = x-(WIDTH/2);
	fractal->mouse_y = y-(HEIGHT/2);
	printf("x = %i y = %i\nmouse_x = %i mouse_y = %i\n", x, y, fractal->mouse_x, fractal->mouse_y);
}

void my_scrollhook(double xdelta, double ydelta, void *param)
{
	t_fractal *fractal;

	fractal = (t_fractal *)param;

	if(ydelta > 0)
		fractal->zoom *= 0.75;
		// printf("zoom in! ydelta = %f\n", ydelta);
	else if (ydelta < 0)
		fractal->zoom *= 1.25;

	mouse_position(fractal);

	fractal->render = true;

}

void close_program(void *param)
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

void init(t_fractal *fractal)
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
        error();
	fractal->img = mlx_new_image(fractal->mlx, WIDTH, HEIGHT);
	if (!fractal->img)
        error();
}

int32_t main(int ac, char *av[])
{
	if (ac < 2)
		ft_error("->>Error: Please specify the type of fractal to display.\n->>Usage: ./fractal_program [Mandelbrot | Julia]");
	
	t_fractal fractal;

	get_set(&fractal, av, ac);
	init(&fractal);
	init_color_palette(&fractal);
	fractal_render(&fractal);
	mlx_key_hook(fractal.mlx, &my_keyhook, &fractal);
	mlx_scroll_hook(fractal.mlx, &my_scrollhook, &fractal);
	mlx_close_hook(fractal.mlx, &close_program, &fractal);
	if (mlx_image_to_window(fractal.mlx, fractal.img, 0, 0) < 0)
        error();
	mlx_loop_hook(fractal.mlx, &render, &fractal);
	mlx_loop(fractal.mlx);
	mlx_terminate(fractal.mlx);
	return (EXIT_SUCCESS);
}
