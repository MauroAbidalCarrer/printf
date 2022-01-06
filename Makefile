# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maabidal <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/29 20:08:50 by maabidal          #+#    #+#              #
#    Updated: 2022/01/06 12:02:38 by maabidal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	ft_printf.c

NAME	= libftprintf.a
CC	= gcc
CFLAGS	= -Wall -Wextra -Werror
RM	= rm -f
OBJS	= $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	ar -rcs $@ $^

.o : .c
	$(CC) $(CFLAGS) -c $< -o $@ -I ./

clean : 
	$(RM) $(OBJS) $(BNSOBJS)

fclean : clean
	$(RM) $(NAME)

re :    fclean all

so:
	$(CC) -fPIC $(CFLAGS) -c $(SRCS) $(BONUSSRCS)
	gcc -shared -o libft.so $(OBJS) $(BNSOBJS)

.PHONY : all clean fclean re
