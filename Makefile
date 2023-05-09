# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: migonzal <migonzal@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/13 09:43:48 by migonzal          #+#    #+#              #
#    Updated: 2023/05/08 12:00:46 by migonzal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### ------ COLORS ------ ###

RED		=	'\033[31m'
GREEN	=	'\033[1;32m'
YELLOW	=	'\033[33m'
BLUE	=	'\033[34m'
PURPLE	=	'\033[1;35m'
CIAN	=	'\033[36m'
WHITE	=	'\033[37m'
NONE	=	'\033[0m'


NAME	=	minishell

LIBFT	=	Libft/libft.a

SRC_DIR	=	./src/

INCLUDE	=	-Iinclude

CC	=	gcc

CFLAGS	=	-g -Wall -Wextra -Werror -fsanitize=address -g3

SRCS	=	$(SRC_DIR)main.c $(SRC_DIR)parser.c $(SRC_DIR)parser_cells.c $(SRC_DIR)cmd.c $(SRC_DIR)split_minishell.c $(SRC_DIR)parse_utils.c ./gnl/get_next_line.c ./gnl/get_next_line_utils.c

OBJS		=	$(SRCS:.c=.o)

.c.o:
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

all			:	$(NAME)

$(NAME)		:	$(LIBFT) $(OBJS)
			@$(CC) $(CFLAGS) $(INCLUDE) -L./libft/ -lft $(OBJS) -o $(NAME)
			@echo $(GREEN) ": All ready to work my pana"

$(LIBFT)	:
				make -C ./libft

clean		:
				@rm -f $(OBJS)
				@make clean -C ./Libft

fclean		:	clean
				@rm $(NAME)
				@make fclean -C ./libft
				@echo $(RED) "Files deleted my pana"

re		:	fclean all


.PHONY: all clean fclean re