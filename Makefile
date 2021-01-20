# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ymori <ymori@student.42tokyo.jp>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/19 00:46:37 by ymori             #+#    #+#              #
#    Updated: 2021/01/21 03:07:03 by ymori            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC := gcc
CFLAGS := -Wall -Wextra -Werror
LIBS = ar -rc
SRCS := ft_atoi.c		\
		ft_bzero.c		\
		ft_strlcpy.c	\
		ft_strlen.c		\
		ft_isalpha.c	\
		ft_isdigit.c	\
		ft_isalnum.c	\
		ft_isascii.c	\
		ft_isprint.c	\
		ft_toupper.c	\
		ft_tolower.c	\
		main.c
OBJS := $(SRCS:.c=.o)
NAME := libft.a

all:	$(NAME)

$(NAME): $(OBJS)
	$(LIBS) $(NAME) $^

$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
