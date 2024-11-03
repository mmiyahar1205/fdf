#include "fdf.h"

int close_window(t_data *data) 
{
    if (data->win_ptr)
        mlx_destroy_window(data->mlx_ptr, data->win_ptr);
    data->win_ptr = NULL;
    free_map(data->pos, data->rows);
    exit(1);
    return (0);
}

int key_press(int keycode, t_data *data) 
{
    if (keycode == ESC_KEY)
        close_window(data);
    return (0);
}
