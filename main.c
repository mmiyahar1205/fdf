/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiyahar <marimiya@sas.upenn.edu>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-03 01:25:18 by mmiyahar          #+#    #+#             */
/*   Updated: 2024-11-03 01:25:18 by mmiyahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	int		fd;
	t_data	data;

	if (argc != 2)
		return (write(2, "Usage: ./fdf <map_file>\n", 23));
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (write(2, "Error opening file\n", 19));
	getmap(fd, &data);
	close(fd);
	if (init_vis(&data) != 0)
		return (free_map(data.pos, data.rows), 1);
	drawmap(&data);
	mlx_key_hook(data.win_ptr, key_press, &data);
	mlx_hook(data.win_ptr, CLOSE_EVENT, 0, close_window, &data);
	mlx_loop(data.mlx_ptr);
	free_map(data.pos, data.rows);
	return (0);
}
