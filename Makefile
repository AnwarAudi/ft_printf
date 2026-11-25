# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aaudi <aaudi@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/11/13 11:50:11 by aaudi             #+#    #+#              #
#    Updated: 2026/11/22 06:39:04 by aaudi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =  libftprintf.a

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS	=  helpers1.c helpers2.c ft_printf.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c ft_printf.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
