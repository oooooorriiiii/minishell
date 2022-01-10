#ifndef LEXER_H
# define LEXER_H

# include <stdbool.h>
# include "minishell.h"
# include "../libft/libft.h"

typedef struct	s_token
{
	int				type;
	char			*val;
	struct s_token	*next;
	struct s_token	*prev;
}				t_token;

// is_quote.c
bool	is_quote(char c);

bool	between_quotes(char *line);

void	lexer(char *original_line, t_token **lex_list);

// token_split_to_list.c
t_list	*token_split_to_list(char *line);

#endif