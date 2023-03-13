# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: migonzal <migonzal@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/28 10:00:25 by migonzal          #+#    #+#              #
#    Updated: 2023/03/13 13:22:56 by migonzal         ###   ########.fr        #
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

HEADER	=	minishell.h

LIBFT	=	Libft/libft.a

SRC_DIR	=	src/ 

INCLUDE	=	-Iinclude

cc	=	gcc

CFLAGS	=	-g -Wall -Wextra -Werror

SRCS	=	$(SRC_DIR)main.c

OBJS		=	$(SRCS:.c=.o)

all			:	$(NAME)

$(NAME)		:	$(OBJS) $(LIBFT) $(HEADER)
			$(CC) $(CFLAGS) $(INCLUDE) $(OBJS) -o $(NAME) $(LIBFT)

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
				
