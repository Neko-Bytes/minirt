LIBFT_DIR = libft
MLX_DIR = minilibx


CC = cc
CFLAGS = -Wall -Wextra -Werror \
         -I$(MLX_DIR) \
         -I$(LIBFT_DIR) \
         -I$(SRC_DIR)

LIBRARIES = $(LIBFT_DIR)/libft.a -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit


NAME = miniRT
SRC_DIR = src
SRC = $(SRC_DIR)/main.c \
	  $(SRC_DIR)/ray_tracing.c \
	  $(SRC_DIR)/window.c \
	  $(SRC_DIR)/vector_ops.c \
	  $(SRC_DIR)/object_array/array.c \
	  $(SRC_DIR)/test/objects.c 
OBJ = $(SRC:.c=.o)


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	@make -C $(MLX_DIR)
	@make -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBRARIES)

all: $(NAME)

clean:
	rm -f $(OBJ)
	@make -C $(MLX_DIR) clean
	@make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
