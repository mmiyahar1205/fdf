#ifndef FDF_H
#define FDF_H

#include "minilibx/mlx.h"
#include "get_next_line.h"
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>
#include <limits.h>
#include <string.h>
#include <limits.h>

#define ESC_KEY 53
#define CLOSE_EVENT 17

#define MALLOC_ERR (write(2, "Memory allocation error\n", 24), EXIT_FAILURE)

typedef struct s_pos {
    float x;
    float y;
    float z;
    int color;
} t_pos;

typedef struct s_data {
    void *mlx_ptr;
    void *win_ptr;
    void *img_ptr;
    char *img_data;
    int bpp;
    int line_len;
    int endian;
    t_pos **pos;
    int rows;
    int cols;
} t_data;

//parsing
int close_window(t_data *data);
int key_press(int keycode, t_data *data);

int	count_words(const char *s, char c);
char	*word_dup(const char *s, int start, int finish);
char	**ft_split(char const *s, char c);

void malloc_err(t_data *data, t_pos *pos);
void getmap(int fd, t_pos ***pos, int *rows, int *cols);
int	ft_atoi(const char *str);
void free_map(t_pos **pos, int rows);

int init_vis(t_data *data);
t_pos apply_isometric_projection(t_pos point, int scale, int offset_x, int offset_y);
void drawline(t_data *data, t_pos start, t_pos dest);
int drawmap(t_data *data);

void *ft_realloc(void *ptr, size_t new_size);
void put_pixel_to_image(t_data *data, int x, int y, int color);

void realloc_map(t_pos ***pos, int *allocated_rows);
void parse_line(char *line, t_pos ***pos, int row_count, int *col_count);
void *ft_memcpy(void *dest, const void *src, size_t n);

#endif