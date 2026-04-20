NAME = cub3d

# OS Detection
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
    MLX_DIR = ./minilibx_opengl
    MLX_FLAGS = -framework AppKit -framework OpenGL
else
    MLX_DIR = ./minilibx_linux
    MLX_FLAGS = -lX11 -lm -lXext
endif

CC = cc
CFLAGS = -g -Wall -Werror -Wextra -I$(INC) $(MLX_INC)

INC = ./inc/
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
MLX = $(MLX_DIR)/libmlx.a
MLX_INC = -I$(MLX_DIR)

REMOVE = rm -f

SRCS = \
./srcs/main.c \
./srcs/error.c \
./srcs/parsing.c \
./srcs/parsing_utils.c \
./srcs/parsing_utils_2.c \
./srcs/utils.c \
./srcs/init.c \
./srcs/rendering.c \
./srcs/events.c \
./srcs/player.c \

OBJS = $(SRCS:.c=.o)

# Colors
GREEN = \033[0;32m
YELLOW = \033[0;33m
CYAN = \033[0;36m
RESET = \033[0m

all: $(NAME)
	@echo "$(GREEN)Compilation successfully done!!$(RESET)"


$(NAME): $(OBJS) $(LIBFT) $(MLX)
	@echo "$(CYAN)Linking cub3d...$(RESET)"
	$(CC) $(CFLAGS) $(OBJS) ./libft/libft.a $(MLX) $(MLX_FLAGS) -o $(NAME)
	@echo "$(GREEN)Cub3d executable created successfully!$(RESET)"

$(LIBFT):
	make -C $(LIBFT_DIR)

$(MLX):
	make -C $(MLX_DIR)

%.o: %.c
	@echo "$(CYAN)Compiling $<...$(RESET)"
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(YELLOW)Cleaning object files...$(RESET)"
	$(REMOVE) $(OBJS)
	make -C $(LIBFT_DIR) clean
	make -C $(MLX_DIR) clean

fclean: clean
	@echo "$(YELLOW)Removing executables...$(RESET)"
	$(REMOVE) $(NAME)
	make -C $(LIBFT_DIR) fclean
	make -C $(MLX_DIR) clean

re: fclean all

.PHONY: all clean fclean re
