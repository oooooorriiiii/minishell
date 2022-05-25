/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymori <ymori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 16:12:30 by ymori             #+#    #+#             */
/*   Updated: 2022/05/25 16:12:30 by ymori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

/**
 *
 * @param curtok
 * @return
 *
 * <redirection> ::= '>' <word>   ->REDIRECTION1
 *                 | '<' <word>   ->REDIRECTION2
 *                 | '>>' <word>  ->REDIRECTION11
 *                 | '<<' <word>  ->REDIRECTION22
 */
t_astree	*REDIRECTION(t_token_list **curtok, bool *nofile)
{
	t_token_list		*save;
	t_astree			*node;

	save = *curtok;
	*curtok = save;
	node = REDIRECTION1(curtok, nofile);
	if (node != NULL || nofile)
		return (node);
	*curtok = save;
	node = REDIRECTION2(curtok, nofile);
	if (node != NULL || nofile)
		return (node);
	*curtok = save;
	node = REDIRECTION11(curtok, nofile);
	if (node != NULL || nofile)
		return (node);
	*curtok = save;
	node = REDIRECTION22(curtok, nofile);
	if (node != NULL || nofile)
		return (node);
	return (NULL);
}

/**
 *
 * @param curtok
 * @return
 *
 * <redirection> <redirection list>
 */
t_astree	*REDIRECTION_LIST1(t_token_list **curtok, bool *nofile)
{
	t_astree	*redirectionNode;
	t_astree	*redirectionListNode;
	t_astree	*result;

	redirectionNode = REDIRECTION(curtok, nofile);
	if (redirectionNode == NULL)
		return (NULL);
	redirectionListNode = REDIRECTION_LIST(curtok, nofile);
	result = malloc(sizeof(t_astree));
	parse_malloc_errordeal(result, NULL);
	astreeset_type(result, NODE_REDIRECTION_LIST);
	astreeset_data(result, NULL);
	astree_attach(result, redirectionNode, redirectionListNode);
	return (result);
}

/**
 *
 * @param curtok
 * @return
 *
 * <redirection list> ::= <redirection> <redirection list> -> REDIRECTION_LIST1
 */
t_astree	*REDIRECTION_LIST(t_token_list **curtok, bool *nofile)
{
	return (REDIRECTION_LIST1(curtok, nofile));
}
