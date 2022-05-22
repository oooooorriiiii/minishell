/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 12:37:31 by sosugimo          #+#    #+#             */
/*   Updated: 2022/02/05 17:57:29 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

/**
 *
 * @param curtok
 * @return
 *
 * <simple command> <command>
 */
t_astree	*COMMAND1(t_token_list **curtok)
{
	t_astree	*simpleCMD;
	t_astree	*cmdNode;
	t_astree	*result;
	char		*pathname;

	simpleCMD = SIMPLECMD(curtok);
	if (simpleCMD == NULL)
		return (NULL);
	if (!term(TOKEN, &pathname, curtok))
	{
		astree_delete(simpleCMD);
		return (NULL);
	}
	cmdNode = CMD(curtok);
	if (cmdNode == NULL)
	{
		astree_delete(simpleCMD);
		return (NULL);
	}
	result = malloc(sizeof(*result));
	parse_malloc_errordeal(result, NULL);
	astreeset_type(result, NODE_CMDPATH);
	return (result);
}

/**
 *
 * @param curtok
 * @return
 *
 * <redirection list> <command>
 */
t_astree	*COMMAND2(t_token_list **curtok)
{

}

/**
 *
 * @param curtok
 * @return
 *
 * <EMPTY>
 */
t_astree	*COMMAND3(t_token_list **curtok)
{
	(void)curtok;
	return (NULL);
}

/**
 *
 * @param curtok
 * @return
 *
 * <command> ::= <simple command> <command>   -> COMMAND1
 *             | <redirection list> <command> -> COMMAND2
 *             | <EMPTY>                      -> COMMAND3
 */
t_astree	*CMD(t_token_list **curtok)
{
	t_token_list	*save;
	t_astree		*node;

	save = *curtok;
	*curtok = save;
	node = COMMAND1(curtok);
	if (node != NULL)
		return (node);
	*curtok = save;
	node = COMMAND2(curtok);
	if (node != NULL)
		return (node);
	return (COMMAND3(curtok));
}

/*
 * current
 * < >
 * ::=	<simple command> '<' <token>
 */
t_astree	*CMD1(t_token_list **curtok)
{
	t_astree	*simplecmdNode;
	t_astree	*result;
	char		*filename;

	simplecmdNode = SIMPLECMD(curtok);
	if (simplecmdNode == NULL)
		return (NULL);
	if (!term(CHAR_LESSER, NULL, curtok))
	{
		astree_delete(simplecmdNode);
		return (NULL);
	}
	if (!term(TOKEN, &filename, curtok))
	{
		astree_delete(simplecmdNode);
		return (NULL);
	}
	result = malloc(sizeof(*result));
	parse_malloc_errordeal(result, NULL);
	astreeset_type(result, NODE_REDIRECT_IN);
	astreeset_data(result, filename);
	astree_attach(result, NULL, simplecmdNode);
	return (result);
}

/*
 * < >
 * ::=	<simple command> '>' <token>
 */
t_astree	*CMD2(t_token_list **curtok)
{
	t_astree	*simplecmdNode;
	t_astree	*result;
	char		*filename;

	simplecmdNode = SIMPLECMD(curtok);
	if (simplecmdNode == NULL)
		return (NULL);
	if (!term(CHAR_GREATER, NULL, curtok))
	{
		astree_delete(simplecmdNode);
		return (NULL);
	}
	if (!term(TOKEN, &filename, curtok))
	{
		astree_delete(simplecmdNode);
		return (NULL);
	}
	result = malloc(sizeof(*result));
	parse_malloc_errordeal(result, NULL);
	astreeset_type(result, NODE_REDIRECT_OUT);
	astreeset_data(result, filename);
	astree_attach(result, NULL, simplecmdNode);
	return (result);
}

t_astree	*CMD3(t_token_list **curtok)
{
	return (SIMPLECMD(curtok));
}
