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
	t_astree	*tokenNode;
	t_astree	*cmdNode;
	t_astree	*result;
	t_astree	*tmpNode;

	puts(" CMD1"); // D
	tokenNode = TOKENLIST(curtok);
	if (tokenNode == NULL)
		return (NULL);
	tokenNode->type = NODE_CMDPATH | NODE_DATA;
	cmdNode = CMD(curtok);
	if (cmdNode == NULL)
		return (tokenNode);
	if (cmdNode->type & NODE_REDIRECTION)
	{
		cmdNode->left->type = NODE_ARGUMENT | NODE_DATA;
		astree_right_node_last(tokenNode)->right = cmdNode->left;
		cmdNode->left = NULL;
		tmpNode = cmdNode->right;
		cmdNode->right = NULL;
		astree_delete(cmdNode);
		cmdNode = tmpNode;
	}
	result = malloc(sizeof(*result));
	parse_malloc_errordeal(result, NULL);
	astreeset_type(result, NODE_REDIRECTION);
	astree_attach(result, tokenNode, cmdNode);
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
	t_astree	*redirectionNode;
	t_astree	*cmdNode;
	t_astree	*result;
	t_astree	*tmpNode;

	puts(" CMD2"); // D
	redirectionNode = REDIRECTION_LIST(curtok);
	if (redirectionNode == NULL)
		return (NULL);
	cmdNode = CMD(curtok);
	if (cmdNode == NULL)
		return (redirectionNode);
	if (cmdNode->type & NODE_REDIRECTION)
	{
		cmdNode->left->type = NODE_ARGUMENT | NODE_DATA;
		astree_right_node_last(redirectionNode)->right = cmdNode->right;
		cmdNode->right = NULL;
		tmpNode = cmdNode->left;
		cmdNode->left = NULL;
		astree_delete(cmdNode);
		cmdNode = tmpNode;
	}
	cmdNode->type = NODE_CMDPATH | NODE_DATA;
	result = malloc(sizeof(*result));
	parse_malloc_errordeal(result, NULL);
	astreeset_type(result, NODE_REDIRECTION);
	astree_attach(result, cmdNode, redirectionNode);
	return (result);
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
	puts(" CMD3"); // D
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

	puts("CMD"); // D
	save = *curtok;
	*curtok = save;
	node = COMMAND1(curtok);
	if (node != NULL)
		return (node);
	*curtok = save;
	node = COMMAND2(curtok);
	if (node != NULL)
		return (node);
	*curtok = save;
	return (COMMAND3(curtok));
}
//
///*
// * current
// * < >
// * ::=	<simple command> '<' <token>
// */
//t_astree	*CMD1(t_token_list **curtok)
//{
//	t_astree	*simplecmdNode;
//	t_astree	*result;
//	char		*filename;
//
//	simplecmdNode = SIMPLECMD(curtok);
//	if (simplecmdNode == NULL)
//		return (NULL);
//	if (!term(CHAR_LESSER, NULL, curtok))
//	{
//		astree_delete(simplecmdNode);
//		return (NULL);
//	}
//	if (!term(TOKEN, &filename, curtok))
//	{
//		astree_delete(simplecmdNode);
//		return (NULL);
//	}
//	result = malloc(sizeof(*result));
//	parse_malloc_errordeal(result, NULL);
//	astreeset_type(result, NODE_REDIRECT_IN);
//	astreeset_data(result, filename);
//	astree_attach(result, NULL, simplecmdNode);
//	return (result);
//}
//
///*
// * < >
// * ::=	<simple command> '>' <token>
// */
//t_astree	*CMD2(t_token_list **curtok)
//{
//	t_astree	*simplecmdNode;
//	t_astree	*result;
//	char		*filename;
//
//	simplecmdNode = SIMPLECMD(curtok);
//	if (simplecmdNode == NULL)
//		return (NULL);
//	if (!term(CHAR_GREATER, NULL, curtok))
//	{
//		astree_delete(simplecmdNode);
//		return (NULL);
//	}
//	if (!term(TOKEN, &filename, curtok))
//	{
//		astree_delete(simplecmdNode);
//		return (NULL);
//	}
//	result = malloc(sizeof(*result));
//	parse_malloc_errordeal(result, NULL);
//	astreeset_type(result, NODE_REDIRECT_OUT);
//	astreeset_data(result, filename);
//	astree_attach(result, NULL, simplecmdNode);
//	return (result);
//}
//
//t_astree	*CMD3(t_token_list **curtok)
//{
//	return (SIMPLECMD(curtok));
//}
