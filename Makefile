cc = cc
NAME=minirt
CFLAGS= -Wextra -Wall -Werror -I/usr/local/includes -I./includes -O3
MLX = -L./lib/minilibx-linux -lmlx -lXext -lX11 -lm

SRCDIR = src
SOURCES := $(shell find $(SRCDIR) -name '*.c')
OBJS := ${SOURCES:.c=.o}
LIBFT= lib/libft/libft.a

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(OBJS) $(MLX) $(LIBFT) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(MLX) :
	$(MAKE) -C ./lib/minilibx-linux

$(LIBFT) :
	$(MAKE) -C ./lib/libft

all: $(NAME)

m: all
	./$(NAME)

clean:
	$(MAKE) -C ./lib/libft clean
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C ./lib/libft fclean
	rm -rf $(NAME)

re: fclean all