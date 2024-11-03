CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC = main.c split.c clean.c init.c utils.c visual.c gnl_utils.c mem_utils.c vis_utils.c
OBJ = $(SRC:.c=.o)
NAME = fdf
MLX_DIR = ./minilibx
MLX = $(MLX_DIR)/libmlx.a
LIBX_FLAGS =  -L$(MLX_DIR) -lmlx -L/usr/X11R6/lib -lX11 -lXext -lXrender -lm

all: $(NAME)

$(NAME): $(OBJ) $(MLX)
	$(CC) $(CFLAGS) $(OBJ) $(MLX) $(LIBX_FLAGS) -o $(NAME)

$(MLX):
	make -C $(MLX_DIR)

clean:
	rm -f $(OBJ)
	make -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(MLX_DIR) clean

re: fclean all
