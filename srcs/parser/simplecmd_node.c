/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simplecmd_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 18:09:21 by sosugimo          #+#    #+#             */
/*   Updated: 2022/05/15 11:44:34 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

/**
 *
 * @param curtok
 * @return
 *
 * <simple command> ::= <pathname> <token list> -> SIMPLECMD1
 */
//t_astree	*SIMPLECMD(t_token_list **curtok)
//{
//	return (SIMPLECMD1(curtok));
//}

/**
 *
 * @param curtok
 * @return
 *
 * <simple command> <token list>
 *
 */
//t_astree	*SIMPLECMD1(t_token_list **curtok)
//{
//	t_astree	*tokenListNode;
//	t_astree	*result;
//	char		*pathname;
//
//	if (!term(TOKEN, &pathname, curtok))
//		return (NULL);
//	tokenListNode = TOKENLIST(curtok);
//	result = malloc(sizeof(t_astree));
//	parse_malloc_errordeal(result, NULL);
//	astreeset_type(result, NODE_CMDPATH);
//	astreeset_data(result, pathname);
//	astree_attach(result, NULL, tokenListNode);
//	return (result);
//}

/**
 *
 * @param curtok
 * @return
 *
 * <token list> ::= <token> <token list> -> TOKENLIST1
 *                | <token>              -> TOKENLIST2
 */
t_astree	*TOKENLIST(t_token_list **curtok)
{
	t_token_list		*save;
	t_astree			*node;

	puts("  tokenlist"); // D
	save = *curtok;
	*curtok = save;
	node = TOKENLIST1(curtok);
	if (node != NULL)
		return (node);
	*curtok = save;
	node = TOKENLIST2(curtok);
	if (node != NULL)
		return (node);
	return (NULL);
}

/**
 *
 * @param curtok
 * @return
 *
 * <token> <token list>
 */
t_astree	*TOKENLIST1(t_token_list **curtok)
{
	t_astree	*tokenListNode;
	t_astree	*result;
	char		*arg;

	puts("  tokenlist1***"); // D
	if (!term(TOKEN, &arg, curtok))
		return (NULL);
	tokenListNode = TOKENLIST(curtok);
	if (tokenListNode == NULL)
	{
		free(arg);
		return (NULL);
	}
	result = malloc(sizeof(*result));
	parse_malloc_errordeal(result, NULL);
	astreeset_type(result, NODE_ARGUMENT | NODE_DATA);
	astreeset_data(result, arg);
	astree_attach(result, NULL, tokenListNode);
	return (result);
}

/**
 *
 * @param curtok
 * @return
 *
 * <token>
 */
t_astree	*TOKENLIST2(t_token_list **curtok)
{
	t_astree	*result;
	char		*arg;

	puts("  tokenlist2"); // D
	if (!term(TOKEN, &arg, curtok))
		return (NULL);
	result = malloc(sizeof(*result));
	parse_malloc_errordeal(result, NULL);
	astreeset_type(result, NODE_ARGUMENT | NODE_DATA);
	astreeset_data(result, arg);
	astree_attach(result, NULL, NULL);
	return (result);
}
