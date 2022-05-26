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

t_astree	*cmd_helper(t_node_type node_type, t_astree *l, t_astree *r)
{
	t_astree	*result;

	result = malloc(sizeof(t_astree));
	parse_malloc_errordeal(result, NULL);
	astreeset_type(result, node_type);
	astreeset_data(result, NULL);
	astree_attach(result, l, r);
	return (result);
}

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
	t_astree	*tmpNode;

	tokenNode = TOKENLIST(curtok);
	if (tokenNode == NULL)
		return (NULL);
	tokenNode->type = NODE_CMDPATH | ELIGIBLE_EXPANSION;
	cmdNode = CMD(curtok);
	if (cmdNode == NULL)
		return (tokenNode);
	if (cmdNode->type & NODE_REDIRECTION)
	{
		cmdNode->left->type = NODE_ARGUMENT | ELIGIBLE_EXPANSION;
		astree_right_node_last(tokenNode)->right = cmdNode->left;
		cmdNode->left = NULL;
		tmpNode = cmdNode->right;
		cmdNode->right = NULL;
		astree_delete(cmdNode);
		cmdNode = tmpNode;
	}
	return (cmd_helper(NODE_REDIRECTION, tokenNode, cmdNode));
}

/**
 *
 * @param curtok
 * @return
 *
 * <redirection list> <command>
 */
t_astree	*COMMAND2(t_token_list **curtok, bool *nofile)
{
	t_astree	*redirectionNode;
	t_astree	*cmdNode;
	t_astree	*tmpNode;

	redirectionNode = REDIRECTION_LIST(curtok, nofile);
	if (redirectionNode == NULL)
		return (NULL);
	cmdNode = CMD(curtok);
	if (cmdNode == NULL)
		return (redirectionNode);
	if (cmdNode->type & NODE_REDIRECTION)
	{
		cmdNode->left->type = NODE_ARGUMENT | ELIGIBLE_EXPANSION;
		astree_right_node_last(redirectionNode)->right = cmdNode->right;
		cmdNode->right = NULL;
		tmpNode = cmdNode->left;
		cmdNode->left = NULL;
		astree_delete(cmdNode);
		cmdNode = tmpNode;
	}
	cmdNode->type = NODE_CMDPATH | ELIGIBLE_EXPANSION;
	return (cmd_helper(NODE_REDIRECTION, cmdNode, redirectionNode));
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
	bool			nofile;

	nofile = false;
	save = *curtok;
	*curtok = save;
	node = COMMAND1(curtok);
	if (node != NULL)
		return (node);
	*curtok = save;
	node = COMMAND2(curtok,&nofile);
	if (node != NULL || nofile == true)
		return (node);
	*curtok = save;
	return (COMMAND3(curtok));
}
