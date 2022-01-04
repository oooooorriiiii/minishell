NAME	=	minishell
CC		=	gcc
CFLAGS	=	-Wall -Werror -Wextra

SRCS_DIR		=	srcs
INCLUDES_DIR	=	-Iincludes \
					-Ilibft

INCLUDES	=	$(INCLUDES_DIR)
SRCS		=	$(SRCS_DIR)/main.c

OBJS		=	$(SRCS:.c=.o)

LIBFT_DIR			=	libft
LIBFT				=	$(LIBFT_DIR)/libft.a

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

.PHONY: all
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -L$(LIBFT_DIR) $(OBJS) -lft -o $(NAME)

.PHONY: clean
clean:
	rm -rf $(OBJS)

.PHONY: fclean
fclean: clean
	rm -rf $(NAME)

.PHONY: re
re: fclean all

$(LIBFT):	$(LIBFT_DIR)/*.c
	make -C $(LIBFT_DIR)

.PHONY: libft_clean
libft_clean:
	make clean -C $(LIBFT_DIR)

.PHONY: libft_fclean
libft_fclean:
	make fclean -C $(LIBFT_DIR)

# ## TEST ##
# TEST		=	test_main.c
# SRCS		=	main.c $(TEST)

# .PHONY: debug
# debug: CFLAGS += -g -fsanitize=ingeger -fsanitize=address -DDEBUG
# debug: re

GTESTDIR	=	./test/gtest
GTEST		=	$(GTESTDIR)/gtest $(GTESTDIR)/googletest-release-1.11.0

TESTDIR		=	./test

# Add the file to be tested
TEST_SRCS	=	is_quote.c

# ADD the test code files
TEST_SCRIPTS	=	is_quote_test.cpp

$(GTEST):
	mkdir -p $(dir $(GTESTDIR))
	curl -OL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.tar.gz
	tar -xvzf release-1.11.0.tar.gz googletest-release-1.11.0
	rm -rf release-1.11.0.tar.gz
	python3 googletest-release-1.11.0/googletest/scripts/fuse_gtest_files.py $(GTESTDIR)
	mv googletest-release-1.11.0 $(GTESTDIR)

.PHONY: test
test: $(GTEST)
	g++ -std=c++11 $(TESTDIR)/$(TEST_SCRIPTS) \
	$(GTESTDIR)/googletest-release-1.11.0/googletest/src/gtest_main.cc \
	$(GTESTDIR)/gtest/gtest-all.cc \
	-I$(GTESTDIR) srcs/$(TEST_SRCS) \
	-Iincludes \
	-lgtest_main -lgtest -lpthread \
	-o tester
	./tester
	rm tester
