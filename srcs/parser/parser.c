/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 12:24:41 by sosugimo          #+#    #+#             */
/*   Updated: 2022/01/20 15:32:00 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

t_astree	*CMDLINE(t_token_list **curtok)
{
	return (JOB(curtok));
}

t_astree	*JOB(t_token_list **curtok)
{
	t_token_list		*save;
	t_astree	*node;

	save = *curtok;
	*curtok = save;
	node = JOB1(curtok);
	if (node != NULL)
		return (node);
	*curtok = save;
	node = JOB2(curtok);
	if (node != NULL)
		return (node);
	return (NULL);
}

t_astree	*JOB1(t_token_list **curtok)
{
	t_astree	*cmdNode;
	t_astree	*jobNode;
	t_astree	*result;

	cmdNode = CMD(curtok);
	if (cmdNode == NULL)
		return (NULL);
	if (!term(CHAR_PIPE, NULL, curtok))
	{
		astree_delete(cmdNode);
		return (NULL);
	}
	jobNode = JOB(curtok);
	if (jobNode == NULL)
	{
		astree_delete(cmdNode);
		return (NULL);
	}
	result = malloc(sizeof(*result));
	astreeset_type(result, NODE_PIPE);
	astree_attach(result, cmdNode, jobNode);
	return (result);
}

t_astree	*JOB2(t_token_list **curtok)
{
	return (CMD(curtok));
}

int	parse(t_lexer *lexbuf, t_astree **syntax_tree)
{
	t_token_list	*curtok;

	// if (lexbuf->ntoks == 0)
	// 	return (-1);
	curtok = lexbuf->list;
	*syntax_tree = CMDLINE(&curtok);
	if (curtok != NULL && curtok->type != 0)
	{
		printf("Syntax Error near: %s\n", curtok->val);
		return (-1);
	}
	return (0);
}
