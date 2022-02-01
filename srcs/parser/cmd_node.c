/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 12:37:31 by sosugimo          #+#    #+#             */
/*   Updated: 2022/02/01 16:15:03 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

t_astree	*CMD(t_token_list **curtok)
{
	t_token_list		*save;
	t_astree			*node;

	save = *curtok;
	*curtok = save;
	node = CMD1(curtok);
	if (node != NULL)
		return (node);
	*curtok = save;
	node = CMD2(curtok);
	if (node != NULL)
		return (node);
	*curtok = save;
	node = CMD11(curtok);
	if (node != NULL)
		return (node);
	*curtok = save;
	node = CMD22(curtok);
	if (node != NULL)
		return (node);
	*curtok = save;
	node = CMD3(curtok);
	if (node != NULL)
		return (node);
	return (NULL);
}

t_astree	*CMD1(t_token_list **curtok)
{
	t_astree	*simplecmdNode;
	t_astree	*result;
	char		*filename;

	simplecmdNode = SIMPLECMD(curtok);
	if (simplecmdNode == NULL)
		return (NULL);
	if (!term(CHAR_LESSER, NULL, curtok))
		return (astree_delete(simplecmdNode));
	if (!term(TOKEN, &filename, curtok))
	{
		free(filename);
		return (astree_delete(simplecmdNode));
	}
	result = malloc(sizeof(*result));
	parse_malloc_errordeal(result, NULL);
	astreeset_type(result, NODE_REDIRECT_IN);
	astreeset_data(result, filename);
	astree_attach(result, NULL, simplecmdNode);
	return (result);
}

t_astree	*CMD2(t_token_list **curtok)
{
	t_astree	*simplecmdNode;
	t_astree	*result;
	char		*filename;

	simplecmdNode = SIMPLECMD(curtok);
	if (simplecmdNode == NULL)
		return (NULL);
	if (!term(CHAR_GREATER, NULL, curtok))
		return (astree_delete(simplecmdNode));
	if (!term(TOKEN, &filename, curtok))
	{
		free(filename);
		return (astree_delete(simplecmdNode));
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
