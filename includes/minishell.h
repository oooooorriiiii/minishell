#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdbool.h>

typedef enum	e_token_type
{
	CHAR_GENERAL		= -1,
	CHAR_PIPE			= '|',
	CHAR_AMPERSAND		= '&',
	CHAR_QOUTE			= '\'',
	CHAR_DQUOTE			= '\"',
	CHAR_SEMICOLON		= ';',
	CHAR_WHITESPACE		= ' ',
	CHAR_ESCAPESEQUENCE	= '\\',
	CHAR_TAB			= '\t',
	CHAR_NEWLINE		= '\n',
	CHAR_GREATER		= '>',
	CHAR_LESSER			= '<',
	CHAR_DBLGREATER		= 'O',
	CHAR_DBLLESSER		= 'I',
	CHAR_NULL			= 0,
	TOKEN				= -1,
}				t_token_type;

# define SINGLE_QUOTE '\''
# define DOUBLE_QUOTE '\"'

bool	is_quote(char c);

#endif