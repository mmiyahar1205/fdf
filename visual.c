/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiyahar <marimiya@sas.upenn.edu>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-03 03:01:35 by mmiyahar          #+#    #+#             */
/*   Updated: 2024-11-03 03:01:35 by mmiyahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	init_vis(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		return (write(2, "Failed to initialize mlx\n", 25));
	data->win_ptr = mlx_new_window(data->mlx_ptr, 1000, 1000, "map");
	if (!data->win_ptr)
		return (write(2, "Failed to create window\n", 24));
	data->img_ptr = mlx_new_image(data->mlx_ptr, 1000, 1000);
	if (!data->img_ptr)
		return (write(2, "Failed to create image\n", 23));
	data->img_data = mlx_get_data_addr(data->img_ptr, &data->bpp,
			&data->line_len, &data->endian);
    if (!data->img_data)
		return (write(2, "Failed to create image\n", 23));
	return (0);
}

t_pos	apply_isometric_projection(t_pos point, int scale, int offset_x,
		int offset_y)
{
	t_pos	iso_point;

	iso_point.x = (point.x - point.y) * cos(M_PI / 6) * scale + offset_x;
	iso_point.y = (point.x + point.y) * sin(M_PI / 6) * scale - point.z * (scale
			/ 4) + offset_y;
	iso_point.z = point.z;
	iso_point.color = point.color;
	return (iso_point);
}

void	drawline(t_data *data, t_pos start, t_pos dest)
{
	float	steps;
	float	curx;
	float	cury;
	int		color;
	int		i;

	steps = fmax(fabs(dest.x - start.x), fabs(dest.y - start.y));
	curx = start.x;
	cury = start.y;
	color = start.color;
	i = 0;
	while (i <= steps)
	{
		if (start.color != dest.color)
			color = get_gradient_color(start.color, dest.color, (float)i
					/ steps);
		put_pixel_to_image(data, round(curx), round(cury), color);
		curx += (dest.x - start.x) / steps;
		cury += (dest.y - start.y) / steps;
		i++;
	}
}

void	drawmap_help(t_data *data, int scale, int offset_x, int offset_y)
{
	int	x;
	int	y;

	x = -1;
	y = -1;
	while (++y < data->rows)
	{
		x = -1;
		while (++x < data->cols)
		{
			if (x + 1 < data->cols)
				drawline(data, apply_isometric_projection(data->pos[y][x],
						scale, offset_x, offset_y),
					apply_isometric_projection(data->pos[y][x + 1], scale,
						offset_x, offset_y));
			if (y + 1 < data->rows)
				drawline(data, apply_isometric_projection(data->pos[y][x],
						scale, offset_x, offset_y),
					apply_isometric_projection(data->pos[y + 1][x], scale,
						offset_x, offset_y));
		}
	}
}

int	drawmap(t_data *data)
{
	int	scale;
	int	offset_x;
	int	offset_y;

	get_scale(data, &scale, &offset_x, &offset_y);
	drawmap_help(data, scale, offset_x, offset_y);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 0, 0);
	return (0);
}
