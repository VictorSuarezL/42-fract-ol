NAME	= fractol
#CFLAGS	:= -Wextra -Wall -Werror -Wunreachable-code -Ofast
LIBMLX	= ./lib/MLX42
CC = gcc
LIBFT_SRC = ./lib/libft/
LIBFT = libft.a
HEADERS	= -I ./includes -I $(LIBMLX)/include -I $(LIBFT_SRC)
LIBS	= $(LIBFT_SRC)$(LIBFT) $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm -framework OpenGL -framework AppKit

SRCS	= $(shell find ./src -iname "*.c")

# SRCS := src/main.c \
# 		src/utils.c \
# 		src/color.c \
# 		src/render.c \
# 		src/hooks.c \

OBJS	= ${SRCS:.c=.o}

# OBJS = $(patsubst %.c, $(OBJ_DIR)/%.o, $(notdir $(SRC_FILES)))

# $(OBJ_DIR):
# 	mkdir -p $(OBJ_DIR)

# $(OBJ_DIR)/%.o: src/%.c Makefile
# 	@$(CC) $(CFLAGS) -c $< -o $@

all: $(LIBFT) libmlx $(NAME)

$(LIBFT):
	make -C $(LIBFT_SRC) bonus

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4 

# $(OBJ_DIR)/%.o: src/%.c
# 	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)"

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)"

$(NAME): $(OBJS)
	$(CC) -g $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	@rm -rf $(OBJS)
	@rm -rf $(LIBMLX)/build
	make -C $(LIBFT_SRC) fclean

fclean: clean
	@rm -rf $(NAME)
	@make -C $(LIBFT_SRC) fclean

re: clean all

.PHONY: all, clean, fclean, re, libmlx