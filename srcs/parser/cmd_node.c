/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdnode.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 12:37:31 by sosugimo          #+#    #+#             */
/*   Updated: 2022/01/17 18:08:45 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

t_astree	*CMD(tok_t **curtok)
{
	tok_t		*save;
	t_astree	*node;

	save = curtok;
	*curtok = save;
	node = CMD1(curtok);
	if (node != NULL)
		return (node);
	*curtok = save;
	node = CMD2(curtok);
	if (node != NULL)
		return (node);
	*curtok = save;
	node = CMD3(curtok);
	if (node != NULL)
		return (node);
	return (NULL);
}

t_astree	*CMD1(tok_t **curtok)
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
		free(filename);
		astree_delete(simplecmdNode);
		return (NULL);
	}
	result = malloc(sizeof(*result));
	dastreeset_type(result, NODE_REDIRECT_IN);
	astreeset_data(result, filename);
	astree_attach(result, NULL, simplecmdNode);
	return (result);
}

t_astree	*CMD2(tok_t **curtok)
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
		free(filename);
		astree_delete(simplecmdNode);
		return (NULL);
	}
	result = malloc(sizeof(*result));
	dastreeset_type(result, NODE_REDIRECT_OUT);
	astreeset_data(result, filename);
	astree_attach(result, NULL, simplecmdNode);
	return (result);
}

t_astree	*CMD3(tok_t **curtok)
{
	return (SIMPLECMD(curtok));
}
