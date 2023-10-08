# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/12 12:33:49 by ele-sage          #+#    #+#              #
#    Updated: 2023/10/08 06:43:38 by ele-sage         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 	miniRT

SRCDIR   	:= srcs
OBJDIR   	:= objs
INCDIR   	:= includes

LIBFT = libft/libft.a
LIBMLX = mlx/libmlx42.a
LIBGLFW = mlx/libglfw3.a

CC = gcc
CFLAGS = -Wall -Werror -Wextra -Ilibft/ -Iinclude/
LDFLAGS = -Llibft/ -Lmlx/
LDLIBS = -framework OpenGL -framework AppKit -framework IOKit -lft -lmlx42 -lglfw3

SRCFILES	= main.c \
		parsing/parse_file.c parsing/check_objs.c parsing/check_components.c \
		objects/add_objs.c objects/create_objs.c objects/init_objs.c \
		utils/error.c utils/ft_free.c \
		vec3/vec3_op1.c vec3/vec3_op2.c \

SRCFILES 	:= $(addprefix $(SRCDIR)/,$(SRCFILES))
OBJFILES 	:= $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCFILES))
INCS    	:= -Ilibft/include -I$(INCDIR) -Imlx/include/MLX42

all: $(NAME)

$(NAME): $(LIBFT) $(LIBMLX) $(OBJFILES)
	$(CC) $(CFLAGS) $(LDFLAGS) $(LDLIBS) $(OBJFILES) -o $(NAME)
	@echo "\033[32m[OK] \033[0m\033[1mCompilation of miniRT\033[0m"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

$(LIBFT):
	@make -C libft

$(LIBMLX):
	@make -C mlx

clean:
	@make clean -C libft
	@make clean -C mlx
	@rm -rf $(OBJDIR)

fclean: clean
	@make fclean -C libft
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
