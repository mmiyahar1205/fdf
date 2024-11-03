#include "fdf.h"

int init_vis(t_data *data) {
    data->mlx_ptr = mlx_init();
    if (!data->mlx_ptr)
        return (printf("Failed to initialize mlx\n"), 1);
    data->win_ptr = mlx_new_window(data->mlx_ptr, 1000, 1000, "map");
    if (!data->win_ptr)
        return (printf("Failed to create window\n"), 1);
    data->img_ptr = mlx_new_image(data->mlx_ptr, 1000, 1000);
    if (!data->img_ptr)
        return (printf("Failed to create image\n"), 1);
    data->img_data = mlx_get_data_addr(data->img_ptr, &data->bpp, &data->line_len, &data->endian);
    return (0);
}

t_pos apply_isometric_projection(t_pos point, int scale, int offset_x, int offset_y) {
    t_pos iso_point;

    iso_point.x = (point.x - point.y) * cos(M_PI / 6) * scale + offset_x;
    iso_point.y = (point.x + point.y) * sin(M_PI / 6) * scale - point.z * (scale / 4) + offset_y;
    iso_point.z = point.z;
    iso_point.color = point.color;
    return (iso_point);
}

void put_pixel_to_image(t_data *data, int x, int y, int color) {
    char *pixel;

    if (x >= 0 && x < 1000 && y >= 0 && y < 1000) 
    {
        pixel = data->img_data + (y * data->line_len + x * (data->bpp / 8));
        *(unsigned int *)pixel = color;
    }
}

int get_gradient_color(int start_color, int dest_color, float ratio) 
{
    int start;
    int dest;
    int red;
    int green;
    int blue;

    start = start_color;
    dest = dest_color;
    red = ((start >> 16) & 0xFF) + (int)((((dest >> 16) & 0xFF) - ((start >> 16) & 0xFF)) * ratio);
    green = ((start >> 8) & 0xFF) + (int)((((dest >> 8) & 0xFF) - ((start >> 8) & 0xFF)) * ratio);
    blue = (start & 0xFF) + (int)(((dest & 0xFF) - (start & 0xFF)) * ratio);
    return (red << 16) | (green << 8) | blue;
}

void drawline(t_data *data, t_pos start, t_pos dest) {
    float steps;
    float curx;
    float cury;
    int color;
    int i;

    steps = fmax(fabs(dest.x - start.x), fabs(dest.y - start.y));
    curx = start.x;
    cury = start.y;
    color = start.color;
    i = 0;
    while (i <= steps) 
    { 
        if(start.color != dest.color)
            color = get_gradient_color(start.color, dest.color, (float)i / steps);
        put_pixel_to_image(data, round(curx), round(cury), color);
        curx += (dest.x - start.x) / steps;
        cury += (dest.y - start.y) / steps;
        i++;
    }
}

int get_minmax(t_data *data, int *min_x, int *max_x, int *min_y)
{
    int y;
    int x;
    int max_y;
    t_pos projected_point;

    y = -1;
    x = -1;
    max_y = INT_MIN;
    while (++y < data->rows)
    {
        x = -1;
        while (++x < data->cols)
        {
            projected_point = apply_isometric_projection(data->pos[y][x], 1, 0, 0);
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

void get_scale(t_data *data, int *scale, int *offset_x, int *offset_y) {
    int min_x;
    int max_x;
    int min_y;
    int max_y;

    min_x = INT_MAX;
    max_x = INT_MIN;
    min_y = INT_MAX;
    max_y = get_minmax(data, &min_x, &max_x, &min_y);
    *scale = fmin(800 / (max_x - min_x), 800 / (max_y - min_y));
    *offset_x = (1000 - (max_x + min_x) * (*scale)) / 2;
    *offset_y = (1000 - (max_y + min_y) * (*scale)) / 2;
}

int drawmap(t_data *data) {
    int x;
    int y;
    int scale;
    int offset_x;
    int offset_y;

    y = -1;
    x = -1;
    get_scale(data, &scale, &offset_x, &offset_y);
    while (++y < data->rows)
    {
        x = -1;
        while (++x < data->cols) 
        {
            if (x + 1 < data->cols)
                drawline(data, apply_isometric_projection(data->pos[y][x], scale, offset_x, offset_y), apply_isometric_projection(data->pos[y][x + 1], scale, offset_x, offset_y));  
            if (y + 1 < data->rows)
                drawline(data, apply_isometric_projection(data->pos[y][x], scale, offset_x, offset_y), apply_isometric_projection(data->pos[y + 1][x], scale, offset_x, offset_y));
        }
    }
    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 0, 0);
    return (0);
}
