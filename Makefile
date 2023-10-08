# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/12 12:33:49 by ele-sage          #+#    #+#              #
#    Updated: 2023/10/08 05:59:15 by ele-sage         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 	miniRT
SRCS = 	main.c \
		parsing/parse_file.c parsing/check_objs.c parsing/check_components.c \
		objects/add_objs.c objects/create_objs.c objects/init_objs.c \
		utils/error.c utils/ft_free.c \
		vec3/vec3_op1.c vec3/vec3_op2.c \

SRCS_DIR = srcs/
SRCS := $(addprefix $(SRCS_DIR), $(SRCS))
OBJS = $(SRCS:.c=.o)
OBJS_DIRS = $(dir $(OBJS))

LIBFT = libft/libft.a
LIBMLX = mlx/libmlx42.a
LIBGLFW = mlx/libglfw3.a

CC = gcc
CFLAGS = -Wall -Werror -Wextra -g

LDFLAGS = -Llibft/ -Lmlx/
LDLIBS = -framework OpenGL -framework AppKit -framework IOKit -lft -lmlx42 -lglfw3

all: lib libmlx $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(LDFLAGS) $(LDLIBS) $(OBJS) -o $(NAME)
	@echo "\033[32mminiRT compiled\033[0m"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "\033[32m$@\033[0m"

lib:
	@$(MAKE) -s -C libft/

libmlx:
	@$(MAKE) -s -C mlx/
	
clean:
	@$(MAKE) -s -C mlx/ clean
	@$(MAKE) -s -C libft/ clean
	@rm -f $(OBJS)
	@rm -rf $(OBJS_DIRS)
	@echo "\033[31mminiRT objects removed\033[0m"

fclean: clean
	@$(MAKE) -C libft/ $@
	@$(MAKE) -C mlx/ $@
	@rm -f $(NAME)
	@echo "\033[31mminiRT removed\033[0m"

re: fclean all
.PHONY: all clean fclean re