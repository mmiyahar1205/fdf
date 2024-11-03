CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC = main.c split.c clean.c init.c utils.c visual.c get_next_line.c get_next_line_utils.c
OBJ = $(SRC:.c=.o)
NAME = fdf
MLX_DIR = ./minilibx
MLX = $(MLX_DIR)/libmlx.a
FRAMEWORKS = -framework OpenGL -framework AppKit  # Only for macOS

all: $(NAME)

$(NAME): $(OBJ) $(MLX)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(MLX) $(FRAMEWORKS)

$(MLX):
	# Compile MiniLibX if not already compiled (C-only)
	make -C $(MLX_DIR)

clean:
	rm -f $(OBJ)
	make -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(MLX_DIR) clean

re: fclean all
