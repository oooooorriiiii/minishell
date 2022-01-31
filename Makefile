NAME	=	minishell
CC		=	gcc
CFLAGS	=	-Wall -Werror -Wextra

SRCS_DIR		=	srcs
INCLUDES_DIR	=	-Iincludes \
					-Ilibft

LIB_READLINE	:=	-lreadline
ifeq ($(shell uname),Darwin)
	INCLUDE_DIR		+=	-I$(shell brew --prefix readline)/include
	LIB_READLINE	+=	-L$(shell brew --prefix readline)/lib
endif

INCLUDES	=	$(INCLUDES_DIR)
SRCS		=	$(SRCS_DIR)/main.c \
				$(SRCS_DIR)/utils/free_str_arr.c \
				$(SRCS_DIR)/utils/free_str.c \
				$(SRCS_DIR)/env/env_list.c \
				$(SRCS_DIR)/env/env_list_clear.c \
				$(SRCS_DIR)/env/env_list_utils.c \
				$(SRCS_DIR)/env/env_name_rule.c \
				$(SRCS_DIR)/env/update_env_val.c \
				$(SRCS_DIR)/env/gen_env_str.c \
				$(SRCS_DIR)/signal/signal.c \
				$(SRCS_DIR)/error/error.c \
				$(SRCS_DIR)/lexer/lexer.c \
				$(SRCS_DIR)/lexer/operator_analysis.c \
				$(SRCS_DIR)/lexer/lexer_utils.c \
				$(SRCS_DIR)/lexer/token_split_to_list.c \
				$(SRCS_DIR)/lexer/token_list_utils.c \
				$(SRCS_DIR)/lexer/token_list_clear.c \
				$(SRCS_DIR)/lexer/helper.c \
				$(SRCS_DIR)/lexer/is_utils.c \
				$(SRCS_DIR)/lexer/heredoc.c \
				$(SRCS_DIR)/parser/ast_visualizer.c \
				$(SRCS_DIR)/parser/astree.c \
				$(SRCS_DIR)/parser/cmd_node_utils.c \
				$(SRCS_DIR)/parser/cmd_node.c \
				$(SRCS_DIR)/parser/parser_utils.c \
				$(SRCS_DIR)/parser/parser.c \
				$(SRCS_DIR)/parser/simplecmd_node.c \
				$(SRCS_DIR)/execute/cd_execute.c \
				$(SRCS_DIR)/execute/child.c \
				$(SRCS_DIR)/execute/dupfor_redirection.c \
				$(SRCS_DIR)/execute/echo_execute.c \
				$(SRCS_DIR)/execute/env_execute.c \
				$(SRCS_DIR)/execute/execute_command_struct.c \
				$(SRCS_DIR)/execute/execute_simple_command.c \
				$(SRCS_DIR)/execute/execute_utils.c \
				$(SRCS_DIR)/execute/execute.c \
				$(SRCS_DIR)/execute/exit_execute.c \
				$(SRCS_DIR)/execute/expansion.c \
				$(SRCS_DIR)/execute/export_execute.c \
				$(SRCS_DIR)/execute/init_struct.c \
				$(SRCS_DIR)/execute/parent.c \
				$(SRCS_DIR)/execute/pwd_execute.c \
				$(SRCS_DIR)/execute/unset_execute.c

OBJS		=	$(SRCS:.c=.o)

LIBFT_DIR			=	libft
LIBFT				=	$(LIBFT_DIR)/libft.a

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

.PHONY: all
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS)  $(OBJS) -L$(LIBFT_DIR) -lft $(READLINE_DIR) -lreadline -o $(NAME)

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
