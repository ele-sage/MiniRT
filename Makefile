# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/12 12:33:49 by ele-sage          #+#    #+#              #
#    Updated: 2023/10/04 12:36:13 by ele-sage         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 	miniRT
SRCS = 	main.c check_elements.c check_utils.c error.c parse.c ft_free.c add_objs.c \
		create_objs1.c create_objs2.c \

SRCS_DIR = srcs/
SRCS := $(addprefix $(SRCS_DIR), $(SRCS))
OBJS_DIRS = objs/
OBJS = $(SRCS:$(SRCS_DIR)%.c=$(OBJS_DIRS)%.o)
DEPS = $(SRCS:%.c=%.d)

INCS = includes/

LIBFT = libft/libft.a
# LIBMLX = mlx/libmlx42.a
# LIBGLFW = mlx/libglfw3.a

CC = gcc
CFLAGS = -Wall -Werror -Wextra -Iincludes -g #-fsanitize=address #-Wunreachable-code -MMD -Ofast
LDFLAGS = -Llibft/ #-Lmlx/
LDLIBS = -lft #-framework OpenGL -framework AppKit -framework IOKit  -lmlx42 -lglfw3

all: lib $(NAME) #libmlx

$(NAME): $(OBJS) $(LIBFT) #$(LIBMLX) $(LIBGLFW)
	@$(CC) $(CFLAGS) $(LDFLAGS) $(LDLIBS) $(OBJS) -o $@
	@echo "\033[32mminiRT compiled\033[0m"

$(OBJS_DIRS)%.o: $(SRCS_DIR)%.c
	@mkdir -p $(OBJS_DIRS)
	@$(CC) $(CFLAGS) -c $< -o $@

lib:
	@$(MAKE) -s -C libft/

# libmlx:
# 	@$(MAKE) -s -C mlx/
	
clean:
#@$(MAKE) -s -C mlx/ clean
	@$(MAKE) -s -C libft/ clean
	@rm -f $(OBJS) $(DEPS)
	@rm -rf $(OBJS_DIRS)
	@echo "\033[31mminiRT objects removed\033[0m"

fclean: clean
	@$(MAKE) -C libft/ $@
#@$(MAKE) -C mlx/ $@
	@rm -f $(NAME)
	@echo "\033[31mminiRT removed\033[0m"

re: fclean all
.PHONY: all clean fclean re
-include $(DEPS)
