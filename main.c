#include "fdf.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	int		fd;
	t_data	data;
	if (argc != 2)
		return (printf("Usage: ./fdf <map_file>\n"), 1);
	fd = open(argv[1], O_RDONLY);
    if(fd == -1)
		return (printf("Error opening file"), 1);
    getmap(fd, &data.pos, &data.rows, &data.cols);
	close(fd);
	if(init_vis(&data) == 1)
		return (free_map(data.pos, data.rows), 1); 
	drawmap(&data);
	mlx_key_hook(data.win_ptr, key_press, &data);
	mlx_hook(data.win_ptr, CLOSE_EVENT, 0, close_window, &data);
	mlx_loop_hook(data.mlx_ptr, drawmap, &data);
	mlx_loop(data.mlx_ptr);
	free_map(data.pos, data.rows);
    return (0);
}
