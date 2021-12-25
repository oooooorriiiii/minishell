NAME	=	a.out
CC		=	gcc
CFLAGS	=	-Wall -Werror -Wextra

SRCSDER		=	.
INCLUDES	=	.
TEST		=	test_main.c
SRCS		=	main.c $(TEST)
OBJS		=	$(SRCS:.c=.o)

.PHONY: all
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

.PHONY: clean
clean:
	rm -rf *.o

.PHONY: fclean
fclean: clean
	rm -rf $(NAME)

.PHONY: re
re: fclean all

## TEST ##

.PHONY: debug
debug: CFLAGS += -g -fsanitize=ingeger -fsanitize=address -DDEBUG
debug: re

GTESTDIR	=	../test
GTEST		=	$(GTESTDIR)/gtest $(GTESTDIR)/googletest-release-1.11.0

TESTDIR		=	.

$(GTEST):
	mkdir -p $(dir ../test)
	curl -OL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.tar.gz
	tar -xvzf release-1.11.0.tar.gz googletest-release-1.11.0
	python3 googletest-release-1.11.0/googletest/scripts/fuse_gtest_files.py $(GTESTDIR)
	mv googletest-release-1.11.0 $(GTESTDIR)

.PHONY: test
test: $(GTEST)
	gcc
