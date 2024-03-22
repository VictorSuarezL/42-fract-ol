/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanz-su <vsanz-su@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 13:25:09 by vsanz-su          #+#    #+#             */
/*   Updated: 2024/03/22 11:47:05 by vsanz-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <MLX42.h>
# include <libft.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define BLACK 0x000000
# define WHITE 0xFFFFFF
# define RED 0xFF0000
# define GREEN 0x00FF00
# define BLUE 0x0000FF
# define YELLOW 0xFFFF00
# define CYAN 0x00FFFF
# define MAGENTA 0xFF00FF
# define ORANGE 0xFFA500
# define PURPLE 0x800080
# define PINK 0xFFC0CB
# define BROWN 0xA52A2A
# define GRAY 0x808080
# define HOT_PINK 0xFF69B4
# define DEEP_PINK 0xFF1493
# define MEDIUM_PURPLE 0x9370DB
# define DARK_ORCHID 0x9932CC
# define LIME_GREEN 0x32CD32
# define DARK_CYAN 0x008B8B
# define GOLD 0xFFD700
# define DARK_MAGENTA 0x8B008B
# define DARK_VIOLET 0x9400D3
# define DEEP_SKY_BLUE 0x00BFFF

# define WIDTH 800
# define HEIGHT 800
# define ITER 70

typedef struct s_color
{
	double		r_o;
	double		g_o;
	double		b_o;
}				t_color;

typedef struct s_fractal
{
	char		*name;
	mlx_t		*mlx;
	mlx_image_t	*img;
	int			escaped_value;
	int			iterations_defined;
	t_color		color;
	uint32_t	palette[ITER];
	double		julia_x;
	double		julia_y;
	bool		render;
	double		shift_x;
	double		shift_y;
	double		zoom;
	int32_t		mouse_x;
	int32_t		mouse_y;

}				t_fractal;

typedef struct s_data
{
	int			set;
	t_color		color;
	uint32_t	palette[2];
}				t_data;

typedef struct s_complex
{
	double		x;
	double		y;
}				t_complex;

// RENDER:
void			fractal_render(t_fractal *fractal);
void			render(void *param);

// HOOKS:
void			my_keyhook(mlx_key_data_t keydata, void *param);
void			my_scrollhook(double xdelta, double ydelta, void *param);
void			close_program(void *param);

// COLOR:
void			init_color_palette(t_fractal *data);
void			shift_palette(t_fractal *fractal);

// UTILS:
double			rescale(double unscaled_num, double new_min, double new_max,
					double old_max);
t_complex		sum_complex(t_complex z1, t_complex z2);
t_complex		square_complex(t_complex z);
t_complex		square_complex_abs(t_complex z);
#endif
