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

bool	between_quotes(char **line);

#endif