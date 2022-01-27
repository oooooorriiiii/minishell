/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 03:37:16 by ymori             #+#    #+#             */
/*   Updated: 2022/01/27 17:08:41 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "execute.h"
# include "lexer.h"
# include "minishell.h"
# include "msh_error.h"
# include "msh_signal.h"
# include "parser.h"
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct _minishell
{
	int		exit_status;
	int		heredoc_status;
	char	*pwd;
}				t_minishell;

extern t_minishell	g_minishell;

typedef enum e_token_type
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