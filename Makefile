# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ymori <ymori@student.42tokyo.jp>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/19 00:46:37 by ymori             #+#    #+#              #
#    Updated: 2021/01/21 01:31:13 by ymori            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC := gcc
CFLAGS := -Wall -Wextra -Werror
LIBS = ar -rc
SRCS := ft_atoi.c		\
		ft_bzero.c		\
		ft_strlcpy.c	\
		ft_strlen.c		\
		main.c
OBJS := $(SRCS:.c=.o)
TARGET := libft.a

all:	$(TARGET)

$(TARGET): $(OBJS)
	$(LIBS) $(TARGET) $^

$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(TARGET)

re: fclean all

.PHONY: all clean fclean re
