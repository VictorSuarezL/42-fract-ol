#include <fractol.h>

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

static void mouse_position(t_fractal *fractal)
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

void render(void *param)
{
	t_fractal *fractal;

	fractal = (t_fractal *)param;

	if(fractal->render)
		fractal_render(fractal);
	fractal->render = false;
}