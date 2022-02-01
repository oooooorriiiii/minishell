/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simplecmd_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 18:09:21 by sosugimo          #+#    #+#             */
/*   Updated: 2022/02/01 16:25:12 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

t_astree	*SIMPLECMD(t_token_list **curtok)
{
	t_token_list	*save;

	save = *curtok;
	return (SIMPLECMD1(curtok));
}

t_astree	*SIMPLECMD1(t_token_list **curtok)
{
	t_astree	*tokenListNode;
	t_astree	*result;
	char		*pathname;

	if (!term(TOKEN, &pathname, curtok))
		return (NULL);
	tokenListNode = TOKENLIST(curtok);
	result = malloc(sizeof(t_astree));
	parse_malloc_errordeal(result, NULL);
	astreeset_type(result, NODE_CMDPATH);
	// printf("1----------  result->type :  %d\n", result->type);
	astreeset_data(result, pathname);
	// printf("2----------  result->type :  %d\n", result->type);
	astree_attach(result, NULL, tokenListNode);
	return (result);
}

t_astree	*TOKENLIST(t_token_list **curtok)
{
	t_token_list		*save;
	t_astree			*node;

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

t_astree	*TOKENLIST1(t_token_list **curtok)
{
	t_astree	*tokenListNode;
	t_astree	*result;
	char		*arg;

	if (!term(TOKEN, &arg, curtok))
		return (NULL);
	tokenListNode = TOKENLIST(curtok);
	result = malloc(sizeof(*result));
	parse_malloc_errordeal(result, NULL);
	astreeset_type(result, NODE_ARGUMENT);
	astreeset_data(result, arg);
	astree_attach(result, NULL, tokenListNode);
	return (result);
}

t_astree	*TOKENLIST2(t_token_list **curtok)
{
	return (NULL);
}
