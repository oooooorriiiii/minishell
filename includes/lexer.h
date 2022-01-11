#ifndef LEXER_H
# define LEXER_H

# include <stdbool.h>
# include "minishell.h"
# include "../libft/libft.h"

# include <stdio.h>

typedef enum	e_token_type
{
	BUILTIN,
	LITERAL,
	PIPE,
	REDIRECT,
	HERE_DOC,
	TOKEN = -1,
}				t_token_type;

typedef struct	s_token
{
	t_token_type	type;
	char			*val;
	// struct s_token	*next;
}				t_token;

typedef struct s_lexer
{
	int		len;
	t_list	*list;
}				t_lexer;


// is_quote.c
bool	is_quote(char c);

void	lexer(char *original_line, t_lexer **lex_list);

// token_split_to_list.c
void	free_set(void **dst, void *src);
t_list	*token_split_to_list(char *line);

// helper.c
void	list_print(t_list *list);
void	list_print_token(t_list *list);

#endif