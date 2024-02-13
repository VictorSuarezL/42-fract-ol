#include <fractol.h>

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