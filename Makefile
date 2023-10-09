# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/12 12:33:49 by ele-sage          #+#    #+#              #
#    Updated: 2023/10/09 15:23:16 by ele-sage         ###   ########.fr        #
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
CFLAGS = -Wall -Werror -Wextra -Ilibft/ -Iinclude/ -fsanitize=address -g
LDFLAGS = -Llibft/ -Lmlx/
LDLIBS = -framework OpenGL -framework AppKit -framework IOKit -lft -lmlx42 -lglfw3

SRCFILES	= main.c \
		init_scene.c render/render.c render/move.c render/hit.c render/thread_render.c \
		parsing/parse_file.c parsing/check_objs.c parsing/check_components.c \
		objects/add_objs.c objects/create_objs.c objects/init_objs.c \
		utils/error.c utils/ft_free.c \
		vec3/vec3_op1.c vec3/vec3_op2.c

SRCFILES 	:= $(addprefix $(SRCDIR)/,$(SRCFILES))
OBJFILES 	:= $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCFILES))
INCS    	:= -Ilibft/include -I$(INCDIR) -Imlx/include/MLX42

GREEN=\033[32m
ERASE=\033[2K\r
RESET=\033[0m
BOLD=\033[1m

all: $(NAME)

$(NAME): $(LIBFT) $(LIBMLX) $(OBJFILES)
	$(CC) $(CFLAGS) $(LDFLAGS) $(LDLIBS) $(OBJFILES) -o $(NAME)
	@echo "$(ERASE)$(GREEN)$(BOLD)$(NAME) created$(RESET)	✅"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	@mkdir -p $(dir $(OBJFILES))
	@$(CC) $(CFLAGS) $(INCS) -c $< -o $@
	
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
