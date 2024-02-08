#ifndef FRACTOL_H
#define FRACTOL_H


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "MLX42/MLX42.h"
#include <libft.h>
#include <string.h>


#define BLACK   0x000000
#define WHITE   0xFFFFFF
#define RED     0xFF0000
#define GREEN   0x00FF00
#define BLUE    0x0000FF
#define YELLOW  0xFFFF00
#define CYAN    0x00FFFF
#define MAGENTA 0xFF00FF
#define ORANGE  0xFFA500
#define PURPLE  0x800080
#define PINK    0xFFC0CB
#define BROWN   0xA52A2A
#define GRAY    0x808080
#define HOT_PINK 0xFF69B4
#define DEEP_PINK 0xFF1493
#define MEDIUM_PURPLE 0x9370DB
#define DARK_ORCHID 0x9932CC
#define LIME_GREEN 0x32CD32
#define DARK_CYAN 0x008B8B
#define GOLD 0xFFD700
#define DARK_MAGENTA 0x8B008B
#define DARK_VIOLET 0x9400D3
#define DEEP_SKY_BLUE 0x00BFFF

#define WIDTH 1000
#define HEIGHT 1000
#define ITER 200

typedef struct s_color
{
	double r_o;
	double g_o;
	double b_o;
} t_color;

typedef struct s_fractal
{
	char *name;
	mlx_t* mlx; // mlx_init
	mlx_image_t* img; // mlx_new_image
	int escaped_value;
	int iterations_defined;
	t_color color;
	uint32_t	palette[ITER];
	double julia_x;
	double julia_y;
	// HOOK VARIABLES TODO
	bool render;
	double shift_x;
	double shift_y;
	double zoom;
	int32_t mouse_x;
	int32_t mouse_y;

} t_fractal;


typedef struct s_data
{
	int set;
	t_color color;
	uint32_t palette[2]; 
} t_data;

typedef struct s_complex
{
	// real
	double x;
	// imaginary
	double y;
} t_complex;

// FUNCTIONS:

// UTILS:
// void get_set(t_fractal *f, char **av);
double rescale(double unscaled_num, double new_min, double new_max, double old_min, double old_max);

t_complex sum_complex(t_complex z1, t_complex z2);

t_complex square_complex(t_complex z);

double ft_atod(char *str);
#endif