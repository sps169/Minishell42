# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: migonzal <migonzal@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/13 09:43:48 by migonzal          #+#    #+#              #
#    Updated: 2023/05/11 12:13:53 by migonzal         ###   ########.fr        #
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

SRC_DIR_PAR	=	./src/parsing/

INCLUDE	=	-Iinclude

CC	=	gcc

CFLAGS	=	-g -Wall -Wextra -Werror -lreadline -fsanitize=address -g3

SRCS	=	$(SRC_DIR)main.c $(SRC_DIR_PAR)parser.c $(SRC_DIR_PAR)parser_cells.c $(SRC_DIR_PAR)cmd.c $(SRC_DIR_PAR)split_minishell.c $(SRC_DIR_PAR)parse_utils.c ./Gnl/get_next_line.c ./Gnl/get_next_line_utils.c

OBJS		=	$(SRCS:.c=.o)

.c.o:
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

all			:	$(NAME)

$(NAME)		:	libft.a $(OBJS)
			@$(CC) $(CFLAGS) $(INCLUDE) $(OBJS) -L. -lft -o $(NAME)
			@echo $(GREEN) ": All ready to work my pana"

libft.a	:
				make -C ./Libft
				mv $(LIBFT) .

clean		:
				@rm -f $(OBJS)
				@rm -f libft.a
				@make clean -C ./Libft

fclean		:	clean
				@rm $(NAME)
				@make fclean -C ./Libft
				@echo $(RED) "Files deleted my pana"

re		:	fclean all


.PHONY: all clean fclean re
