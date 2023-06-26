# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: esamad-j <esamad-j@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/15 04:44:20 by esamad-j          #+#    #+#              #
#    Updated: 2023/06/26 11:51:08 by esamad-j         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#-g -fsanitize=address -g3

NAME	= pipex

SRCS	= ft_split.c lib_ft.c main.c exit.c childs.c path_error.c

OBJS		= $(SRCS:%.c=%.o)

CFLAGS		=  -Wall -Werror -Wextra -g

CC 			= gcc 

all: $(NAME)

$(NAME): $(OBJS)
	$(CC)   $(FLAGS)  $(SRCS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re