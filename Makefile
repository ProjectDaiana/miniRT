cc = cc
NAME = miniRT
CFLAGS = -Wextra -Wall -Werror -I/usr/local/includes -I./includes
MLX = -L./lib/minilibx-linux -lmlx -lXext -lX11 -lm

SRCDIR = src
BONUS_SRCDIR = src_bonus

BONUS_FILES := src/render/render.c src/render/intersect_cylinder.c
BONUS_REPLACEMENT = src_bonus/bonus_render.c src_bonus/bonus_intersect_cylinder.c
BONUS_ADDITIONAL = src_bonus/bonus_render_threads.c src_bonus/bonus_thread_helpers.c

SOURCES = $(shell find $(SRCDIR) -name '*.c')
OBJS = $(SOURCES:.c=.o)

BONUS_SOURCES = $(filter-out $(BONUS_FILES), $(SOURCES))
BONUS_SOURCES += $(BONUS_REPLACEMENT) $(BONUS_ADDITIONAL)
BONUS_OBJS = $(BONUS_SOURCES:.c=.o)

LIBFT= lib/libft/libft.a

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(OBJS) $(MLX) $(LIBFT) -o $(NAME)

bonus: fclean $(BONUS_OBJS) $(LIBFT)
	@$(CC) $(BONUS_OBJS) $(MLX) $(LIBFT) -o $(NAME)

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
	rm -f $(OBJS) $(BONUS_OBJS)

fclean: clean
	$(MAKE) -C ./lib/libft fclean
	rm -rf $(NAME)

re: fclean all
