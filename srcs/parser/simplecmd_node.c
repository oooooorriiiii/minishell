/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simplecmd_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 18:09:21 by sosugimo          #+#    #+#             */
/*   Updated: 2022/01/17 18:09:39 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_astree	*SIMPLECMD(tok_t **curtok)
{
	tok_t	*save;

	save = curtok;
	return (SIMPLECMD1(curtok));
}

t_astree	*SIMPLECMD1(tok_t **curtok)
{
	t_astree	*tokenListNode;
	t_astree	*result;
	char		*pathname;

	if (!term(TOKEN, &pathname, curtok))
		return (NULL);
	tokenListNode = TOKENLIST(curtok);
	result = malloc(sizeof(*result));
	dastreeset_type(result, NODE_CMDPATH);
	astreeset_data(result, pathname);
	astree_attach(result, NULL, tokenListNode);
	return (result);
}

t_astree	*TOKENLIST(tok_t **curtok)
{
	tok_t		*save;
	t_astree	*node;

	save  = curtok;
	curtok = save;
	node = TOKENLIST1(curtok);
	if (node != NULL)
		return (node);
	save  = curtok;
	curtok = save;
	node = TOKENLIST2(curtok);
	if (node != NULL)
		return (node);
	return (NULL);
}

t_astree	*TOKENLIST1(tok_t **curtok)
{
	t_astree	*tokenListNode;
	t_astree	*result;
	char		*arg;

	if (!term(TOKEN, &arg, curtok))
		return (NULL);
	tokenListNode = TOKENLIST(curtok);
	result = malloc(sizeof(*result));
	dastreeset_type(result, NODE_ARGUMENT);
	astreeset_data(result, arg);
	astree_attach(result, NULL, tokenListNode);
	return (result);
}

t_astree	*TOKENLIST2(tok_t **curtok)
{
	return (NULL);
}
