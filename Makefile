NAME	=	minishell
CC		=	gcc
CFLAGS	=	-Wall -Werror -Wextra

SRCS_DIR		=	srcs
INCLUDES_DIR	=	-Iincludes \
					-Ilibft

INCLUDES	=	$(INCLUDES_DIR)
SRCS		=	$(SRCS_DIR)/main.c \
				$(SRCS_DIR)/lexer/lexer.c \
				$(SRCS_DIR)/lexer/token_split_to_list.c \
				$(SRCS_DIR)/lexer/token_list_utils.c \
				$(SRCS_DIR)/lexer/helper.c \
				$(SRCS_DIR)/lexer/is_quote.c

OBJS		=	$(SRCS:.c=.o)

LIBFT_DIR			=	libft
LIBFT				=	$(LIBFT_DIR)/libft.a

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

.PHONY: all
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS)  $(OBJS) -L$(LIBFT_DIR) -lft -o $(NAME)

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

.PHONY: debug
debug: CFLAGS += -g -fsanitize=undefined -fsanitize=address -DDEBUG
debug: re

##########
## TEST ##
##########

GTESTDIR	=	./test/gtest
GTEST		=	$(GTESTDIR)/gtest $(GTESTDIR)/googletest-release-1.11.0

TESTDIR		=	./test

# Add the file to be tested
TEST_SRCS	=	srcs/lexer/is_quote.c \
				srcs/lexer/insert_spaces.c

TEST_SRCS_OBJS	=	$(TEST_SRCS:.c=.o)

%.o: %.c
	$(CC) $(INCLUDES) -c $< -o $@
# ADD the test code files
TEST_SCRIPTS	=	$(TESTDIR)/is_quote_test.cpp \
					$(TESTDIR)/between_quotes_test.cpp

$(GTEST):
	mkdir -p $(dir $(GTESTDIR))
	curl -OL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.tar.gz
	tar -xvzf release-1.11.0.tar.gz googletest-release-1.11.0
	rm -rf release-1.11.0.tar.gz
	python3 googletest-release-1.11.0/googletest/scripts/fuse_gtest_files.py $(GTESTDIR)
	mv googletest-release-1.11.0 $(GTESTDIR)

.PHONY: test
test: $(GTEST) $(TEST_SRCS_OBJS)
	g++ -std=c++11 \
	-fsanitize=address \
	$(GTESTDIR)/googletest-release-1.11.0/googletest/src/gtest_main.cc \
	$(GTESTDIR)/gtest/gtest-all.cc \
	-I$(GTESTDIR) -Iincludes \
	$(TEST_SCRIPTS) \
	$(TEST_SRCS_OBJS) \
	-lgtest_main -lgtest -L$(LIBFT_DIR) -lft -lpthread \
	-o tester
	./tester
	rm tester
