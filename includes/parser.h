/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 01:00:52 by sosugimo          #+#    #+#             */
/*   Updated: 2022/04/27 18:53:01 by sosugimo         ###   ########.fr       */
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

typedef enum e_node_type
{
	NODE_PIPE				= (1 << 0),
	NODE_REDIRECTION_LIST	= (1 << 1),
	NODE_REDIRECTION		= (1 << 2),
	NODE_REDIRECT_IN		= (1 << 3),
	NODE_REDIRECT_OUT		= (1 << 4),
	NODE_REDIRECT_D_IN		= (1 << 5),
	NODE_REDIRECT_D_OUT		= (1 << 6),
	NODE_CMDPATH			= (1 << 7),
	NODE_ARGUMENT			= (1 << 8),
	ELIGIBLE_EXPANSION		= (1 << 9),
}		t_node_type;

typedef struct astree
{
	t_node_type		type;
	char			*szData;
	struct astree	*left;
	struct astree	*right;
}				t_astree;

t_astree		*CMDLINE(t_token_list **curtok, bool *nofile);

t_astree		*JOB(t_token_list **curtok, bool *nofile);
t_astree		*JOB1(t_token_list **curtok, bool *nofile);
t_astree		*JOB2(t_token_list **curtok, bool *nofile);

t_astree		*CMD(t_token_list **curtok, bool *nofile);

t_astree		*REDIRECTION_LIST(t_token_list **curtok, bool *nofile);
t_astree		*REDIRECTION(t_token_list **curtok, bool *nofile);

t_astree		*REDIRECTION1(t_token_list **curtok, bool *nofile);
t_astree		*REDIRECTION2(t_token_list **curtok, bool *nofile);
t_astree		*REDIRECTION11(t_token_list **curtok, bool *nofile);
t_astree		*REDIRECTION22(t_token_list **curtok, bool *nofile);

t_astree		*TOKENLIST(t_token_list **curtok, bool *nofile);
t_astree		*TOKENLIST1(t_token_list **curtok, bool *nofile);
t_astree		*TOKENLIST2(t_token_list **curtok);

int				parse(t_lexer *lexbuf, t_astree **syntax_tree);
bool			term(int toketype, char **bufferptr, t_token_list **curtok);

bool			trim_x(t_token_list **curtok, t_token_type type);
bool			trim_alloc(t_token_list **curtok, char **bufptr);

void			astree_attach(t_astree	*root,
					t_astree	*leftNode, t_astree	*rightNode);
void			astreeset_type(t_astree	*node, t_node_type nodetype);
void			astreeset_data(t_astree	*node, char	*data);
void			astree_delete(t_astree	*node);
t_astree		*astree_right_node_last(t_astree *node);
void			parse_malloc_errordeal(t_astree *buf1, char *buf2);

void			print_syntax_tree(t_astree *tree);

void			expansion(t_astree *astree);

#endif
