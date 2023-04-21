# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sperez-s <sperez-s@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/28 10:00:25 by migonzal          #+#    #+#              #
#    Updated: 2023/04/21 13:19:35 by sperez-s         ###   ########.fr        #
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

CFLAGS	=	-g -Wall -Wextra -Werror

SRCS	=	$(SRC_DIR)main.c			\
			$(SRC_DIR)builtins/echo.c	\

OBJS		=	$(SRCS:.c=.o)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

all			:	$(NAME)

$(NAME)		:	$(LIBFT) $(OBJS)
			$(CC) $(CFLAGS) $(INCLUDE) -L./libft/ -lft $(OBJS) -o $(NAME)

$(LIBFT)	:
				make -C ./libft

clean		:
				rm -rf $(OBJS)
				make clean -C ./Libft

fclean		:	clean
				rm $(NAME)
				make fclean -C ./libft

re		:	fclean all


.PHONY: all clean fclean re
				
