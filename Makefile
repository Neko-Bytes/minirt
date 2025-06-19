# Directories
LIBFT_DIR = libft
MLX_DIR = minilibx
BUILD_DIR = $(MLX_DIR)/build
GNL_DIR     = gnl
SRC_DIR = src
INCLUDE_DIR = includes

# Compiler & Flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address \
		 -I$(MLX_DIR)/include \
		 -I$(LIBFT_DIR) \
		 -I$(SRC_DIR) \
		 -I$(INCLUDE_DIR)

# macOS specific flags
MAC_FLAGS = -framework Cocoa -framework OpenGL -framework IOKit \
			-L/opt/homebrew/Cellar/glfw/3.4/lib -lglfw

# Linux specific flags
LINUX_FLAGS = -L$(BUILD_DIR) -lmlx42 -L/usr/X11/lib -lX11 -lXext -lglfw -lm

# Sources
NAME = miniRT
SRC = $(SRC_DIR)/main.c \
	  $(SRC_DIR)/ray_tracing/ray_tracing.c \
	  $(SRC_DIR)/light/point_light.c \
	  $(SRC_DIR)/light/hard_shadow.c \
	  $(SRC_DIR)/render/window.c \
	  $(SRC_DIR)/render/keys.c \
	  $(SRC_DIR)/math/vector_ops.c \
	  $(SRC_DIR)/object_array/array.c \
	  $(SRC_DIR)/gc/gc.c \
	  $(SRC_DIR)/utils/print_utils.c \
	  $(SRC_DIR)/parsing/parse_args.c \
      $(SRC_DIR)/parsing/parse_file.c \
      $(SRC_DIR)/parsing/parse_light.c \
      $(SRC_DIR)/parsing/parse_plane.c \
      $(SRC_DIR)/parsing/parse_sphere.c \
      $(SRC_DIR)/parsing/parse_cylinder.c \
      $(SRC_DIR)/parsing/parse_ambient.c \
      $(SRC_DIR)/parsing/parse_camera.c \
	  $(SRC_DIR)/errors/errors.c \
	  $(SRC_DIR)/math/intersect.c  \
	  src/utils/parse_elements_utils.c \
	  $(GNL_DIR)/get_next_line.c \
      $(GNL_DIR)/get_next_line_utils.c 

OBJ = $(SRC:.c=.o)

# Object rules
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Helper to build MLX42
mlx42:
	@if [ ! -f $(BUILD_DIR)/libmlx42.a ]; then \
		echo "Building MLX42..."; \
		mkdir -p $(BUILD_DIR) && cd $(BUILD_DIR) && cmake .. && make; \
	fi

# macOS build
mac: CFLAGS += -D MACOS
mac: mlx42 $(OBJ)
	@make -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBFT_DIR)/libft.a \
		-L$(BUILD_DIR) -lmlx42 $(MAC_FLAGS)

# Linux build
linux: CFLAGS += -D LINUX
linux: mlx42 $(OBJ)
	@make -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBFT_DIR)/libft.a $(LINUX_FLAGS)

# Default target
all: mac

# Cleanup
clean:
	rm -f $(OBJ)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re mac linux mlx42
