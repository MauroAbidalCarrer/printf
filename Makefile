# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maabidal <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/29 20:08:50 by maabidal          #+#    #+#              #
#    Updated: 2022/01/12 16:04:02 by maabidal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =		ft_printf.c
BONUSSRCS = 	ft_printf_bonus.c\
		ft_printf_utils_bonus.c

NAME	= libftprintf.a
CC	= gcc
CFLAGS	= -Wall -Wextra -Werror
RM	= rm -f
OBJS	= $(SRCS:.c=.o)
BNSOBJS	= $(BONUSSRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	ar -rcs $@ $^

bonus : $(BNSOBJS)
	ar -rcs $(NAME) $(BNSOBJS)

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
