/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiyahar <marimiya@sas.upenn.edu>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-03 03:12:07 by mmiyahar          #+#    #+#             */
/*   Updated: 2024-11-03 03:12:07 by mmiyahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	get_minmax(t_data *data, float *min_x, float *max_x, float *min_y)
{
	int		y;
	int		x;
	float	max_y;
	t_pos	projected_point;

	y = -1;
	max_y = -1e9;
	while (++y < data->rows)
	{
		x = -1;
		while (++x < data->cols)
		{
			projected_point = apply_isometric_projection(data->pos[y][x], 1, 0,
					0);
			if (projected_point.x < *min_x)
				*min_x = projected_point.x;
			else if (projected_point.x > *max_x)
				*max_x = projected_point.x;
			if (projected_point.y < *min_y)
				*min_y = projected_point.y;
			else if (projected_point.y > max_y)
				max_y = projected_point.y;
		}
	}
	return (max_y);
}

void	get_scale(t_data *data, float *scale, float *offset_x, float *offset_y)
{
	float	min_x;
	float	max_x;
	float	min_y;
	float	max_y;

	min_x = 1e9;
	max_x = -1e9;
	min_y = 1e9;
	max_y = get_minmax(data, &min_x, &max_x, &min_y);
	*scale = fmin(800 / (max_x - min_x), 800 / (max_y - min_y));
	*offset_x = (1000 - (max_x + min_x) * (*scale)) / 2;
	*offset_y = (1000 - (max_y + min_y) * (*scale)) / 2;
}

void	put_pixel_to_image(t_data *data, int x, int y, int color)
{
	char	*pixel;

	if (x >= 0 && x < 1000 && y >= 0 && y < 1000)
	{
		pixel = data->img_data + (y * data->line_len + x * (data->bpp / 8));
		*(unsigned int *)pixel = color;
	}
}

int	get_gradient_color(int start_color, int dest_color, float ratio)
{
	int	start;
	int	dest;
	int	red;
	int	green;
	int	blue;

	start = start_color;
	dest = dest_color;
	red = ((start >> 16) & 0xFF) + (int)((((dest >> 16) & 0xFF)
				- ((start >> 16) & 0xFF)) * ratio);
	green = ((start >> 8) & 0xFF) + (int)((((dest >> 8) & 0xFF)
				- ((start >> 8) & 0xFF)) * ratio);
	blue = (start & 0xFF) + (int)(((dest & 0xFF) - (start & 0xFF)) * ratio);
	return ((red << 16) | (green << 8) | blue);
}
