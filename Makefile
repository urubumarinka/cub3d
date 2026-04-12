NAME = cub3d

CC = cc
CFLAGS = -g -Wall -Werror -Wextra -I$(INC) -Imlx

INC = ./inc/
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

REMOVE = rm -f

SRCS = \
./srcs/main.c \
./srcs/error.c \
./srcs/parsing.c \

OBJS = $(SRCS:.c=.o)

# Colors
GREEN = \033[0;32m
YELLOW = \033[0;33m
CYAN = \033[0;36m
RESET = \033[0m

all: $(NAME)
	@echo "$(GREEN)Compilation successfully done!!$(RESET)"


$(NAME): $(OBJS) $(LIBFT)
	@echo "$(CYAN)Linking cub3d...$(RESET)"
	$(CC) $(CFLAGS) $(OBJS) ./libft/libft.a  -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)
	@echo "$(GREEN)Cub3d executable created successfully!$(RESET)"

$(LIBFT):
	make -C $(LIBFT_DIR)

%.o: %.c
	@echo "$(CYAN)Compiling $<...$(RESET)"
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(YELLOW)Cleaning object files...$(RESET)"
	$(REMOVE) $(OBJS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	@echo "$(YELLOW)Removing executables...$(RESET)"
	$(REMOVE) $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
