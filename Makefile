NAME	= fractol
CFLAGS	:= -Wextra -Wall -Werror
LIBMLX	= ./lib/MLX42
CC = gcc
LIBFT_SRC = ./lib/libft/
LIBFT = libft.a
MLX = libmlx42.a
USER = vsanz-su
HEADERS	= -I ./includes -I $(LIBMLX)/include/MLX42 -I $(LIBFT_SRC)
LIBS = $(LIBFT_SRC)$(LIBFT) $(LIBMLX)/libmlx42.a -lglfw -L"/Users/vsanz-su/.brew/opt/glfw/lib/"

SRCS := src/main.c \
		src/utils.c \
		src/color.c \
		src/render.c \
		src/hooks.c \

OBJS	= ${SRCS:.c=.o}

all: $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_SRC)

$(MLX):
	@$(MAKE) -C $(LIBMLX)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	$(CC) -g $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	@rm -rf $(OBJS)
	@$(MAKE) -C $(LIBMLX) clean
	@$(MAKE) -C $(LIBFT_SRC) clean

fclean: clean
	@$(MAKE) -C $(LIBFT_SRC) fclean
	@$(MAKE) -C $(LIBMLX) fclean
	@rm -rf $(NAME)

re: fclean $(NAME)

.PHONY: all, clean, fclean, re
