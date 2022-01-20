/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 01:00:52 by sosugimo          #+#    #+#             */
/*   Updated: 2022/01/20 15:34:07 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdbool.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>

# include "lexer.h"
# include "minishell.h"
typedef	enum
{
	NODE_PIPE			= (1 << 0),
	NODE_BCKGRND		= (1 << 1),
	NODE_SEQ			= (1 << 2),
	NODE_REDIRECT_IN	= (1 << 3),
	NODE_REDIRECT_OUT	= (1 << 4),
	NODE_REDIRECT_D_IN	= (1 << 5),
	NODE_REDIRECT_D_OUT = (1 << 6),
	NODE_CMDPATH		= (1 << 7),
	NODE_ARGUMENT		= (1 << 8),
	NODE_DATA			= (1 << 9),
}		NodeType;

enum TokenType
{
	CHAR_GENERAL		= -1,
	CHAR_PIPE			= '|',
	CHAR_AMPERSAND		= '&',
	CHAR_QOUTE			= '\'',
	CHAR_DQUOTE			= '\"',
	CHAR_SEMICOLON		= ';',
	CHAR_WHITESPACE		= ' ',
	CHAR_ESCAPESEQUENCE = '\\',
	CHAR_TAB			= '\t',
	CHAR_NEWLINE		= '\n',
	CHAR_GREATER		= '>',
	CHAR_LESSER			= '<',
	CHAR_DBLGREATER		= 'O',
	CHAR_DBLLESSER		= 'I',
	CHAR_NULL			= 0,
};

typedef	struct	astree
{
	int				type;
	char			*szData;
	struct astree	*left;
	struct astree	*right;
}				t_astree;

t_astree		*CMDLINE(t_token_list **curtok);

t_astree		*JOB(t_token_list **curtok);
t_astree		*JOB1(t_token_list **curtok);
t_astree		*JOB2(t_token_list **curtok);

t_astree		*CMD(t_token_list **curtok);
t_astree		*CMD1(t_token_list **curtok);
t_astree		*CMD2(t_token_list **curtok);
t_astree		*CMD11(t_token_list **curtok);
t_astree		*CMD22(t_token_list **curtok);
t_astree		*CMD3(t_token_list **curtok);

t_astree		*SIMPLECMD(t_token_list **curtok);
t_astree		*SIMPLECMD1(t_token_list **curtok);

t_astree		*TOKENLIST(t_token_list **curtok);
t_astree		*TOKENLIST1(t_token_list **curtok);
t_astree		*TOKENLIST2(t_token_list **curtok);

bool			term(int toketype, char **bufferptr, t_token_list **curtok);

void			astree_attach(t_astree	*root,
					t_astree	*leftNode, t_astree	*rightNode);
void			astreeset_type(t_astree	*node, NodeType nodetype);
void			astreeset_data(t_astree	*node, char	*data);
void			astree_delete(t_astree	*node);

#endif
