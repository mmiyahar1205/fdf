/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiyahar <marimiya@sas.upenn.edu>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-03 03:01:02 by mmiyahar          #+#    #+#             */
/*   Updated: 2024-11-03 03:01:02 by mmiyahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "minilibx/mlx.h"
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define ESC_KEY 65307
# define CLOSE_EVENT 17
# define BUFFER_SIZE 4

typedef struct s_pos
{
	float	x;
	float	y;
	float	z;
	int		color;
}			t_pos;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*img_data;
	int		bpp;
	int		line_len;
	int		endian;
	t_pos	**pos;
	int		rows;
	int		cols;
}			t_data;

int			close_window(t_data *data);
int			key_press(int keycode, t_data *data);
int			count_words(const char *s, char c);
char		*word_dup(const char *s, int start, int finish);
char		**ft_split(char const *s, char c);
void		getmap(int fd, t_data *data);
int			ft_atoi(const char *str);
void		free_map(t_pos **pos, int rows);
int			init_vis(t_data *data);
t_pos		apply_isometric_projection(t_pos point, int scale, int offset_x,
				int offset_y);
void		drawline(t_data *data, t_pos start, t_pos dest);
int			drawmap(t_data *data);
void		*ft_realloc(void *ptr, size_t new_size);
void		put_pixel_to_image(t_data *data, int x, int y, int color);
void		realloc_map(t_data *data, int *allocated_rows);
void		parse_line(char *line, t_data *data);
void		get_listlen(t_data *data, char **values);
void		*ft_memcpy(void *dest, const void *src, size_t n);
char		*get_next_line(int fd, t_data *data);
size_t		ft_strlen(const char *s);
int			find_nextline(char *buffer);
void		clean_buff(char *buffer, int i);
char		*append_line(char *line, char *buffer, int i, t_data *data);
char		*read_file(int fd, char *line, char *buffer, t_data *data);
void		parse_line_err(char *line, t_data *data, char **values);
void		free_strlist(char **str);
void		free_map(t_pos **pos, int rows);
int			get_gradient_color(int start_color, int dest_color, float ratio);
void		get_scale(t_data *data, int *scale, int *offset_x, int *offset_y);
void		malloc_err(void);

#endif