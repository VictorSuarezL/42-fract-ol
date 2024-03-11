/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanz-su <vsanz-su@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 13:24:36 by vsanz-su          #+#    #+#             */
/*   Updated: 2024/03/04 12:34:22 by vsanz-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

double	rescale(double unscaled_num, double new_min, double new_max,
		double old_max)
{
	double	old_min;

	old_min = 0;
	unscaled_num = (new_max - new_min) * (unscaled_num - old_min) / (old_max
			- old_min) + new_min;
	return (unscaled_num);
}

t_complex	sum_complex(t_complex z1, t_complex z2)
{
	t_complex	result;

	result.x = z1.x + z2.x;
	result.y = z1.y + z2.y;
	return (result);
}

t_complex	square_complex(t_complex z)
{
	t_complex	result;

	result.x = (z.x * z.x) - (z.y * z.y);
	result.y = 2 * z.x * z.y;
	return (result);
}

t_complex	square_complex_abs(t_complex z)
{
	t_complex	result;

	result.x = (z.x * z.x) - (z.y * z.y);
	result.y = fabs(2 * z.x * z.y);
	return (result);
}
