/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdnode.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 12:37:31 by sosugimo          #+#    #+#             */
/*   Updated: 2022/01/17 12:39:51 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

t_astree	*CMD(void)
{
	tok_t		*save;
	t_astree	*node;

	save = curtok;
	curtok = save;
	node = CMD1();
	if (node != NULL)
		return (node);
	curtok = save;
	node = CMD2();
	if (node != NULL)
		return (node);
	curtok = save;
	node = CMD3();
	if (node != NULL)
		return (node);
	return (NULL);
}

t_astree	*CMD1(void)
{
	t_astree	*simplecmdNode;
	t_astree	*result;
	char		*filename;

	simplecmdNode = SIMPLECMD();
	if (simplecmdNode == NULL)
		return (NULL);
	if (!term(CHAR_LESSER, NULL))
	{
		astree_delete(simplecmdNode);
		return (NULL);
	}
	if (!term(TOKEN, &filename))
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

t_astree	*CMD2(void)
{
	t_astree	*simplecmdNode;
	t_astree	*result;
	char		*filename;

	simplecmdNode = SIMPLECMD();
	if (simplecmdNode == NULL)
		return (NULL);
	if (!term(CHAR_GREATER, NULL))
	{
		astree_delete(simplecmdNode);
		return (NULL);
	}
	if (!term(TOKEN, &filename))
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

t_astree	*CMD3(void)
{
	return (SIMPLECMD());
}

t_astree	*SIMPLECMD(void)
{
	tok_t	*save;

	save = curtok;
	return (SIMPLECMD1());
}

t_astree	*SIMPLECMD1(void)
{
	t_astree	*tokenListNode;
	t_astree	*result;
	char		*pathname;

	if (!term(TOKEN, &pathname))
		return (NULL);
	tokenListNode = TOKENLIST();
	result = malloc(sizeof(*result));
	dastreeset_type(result, NODE_CMDPATH);
	astreeset_data(result, pathname);
	astree_attach(result, NULL, tokenListNode);
	return (result);
}

t_astree	*TOKENLIST(void)
{
	tok_t		*save;
	t_astree	*node;

	save  = curtok;
	curtok = save;
	node = TOKENLIST1();
	if (node != NULL)
		return (node);
	save  = curtok;
	curtok = save;
	node = TOKENLIST2();
	if (node != NULL)
		return (node);
	return (NULL);
}

t_astree	*TOKENLIST1(void)
{
	t_astree	*tokenListNode;
	t_astree	*result;
	char		*arg;

	if (!term(TOKEN, &arg))
		return (NULL);
	tokenListNode = TOKENLIST();
	result = malloc(sizeof(*result));
	dastreeset_type(result, NODE_ARGUMENT);
	astreeset_data(result, arg);
	astree_attach(result, NULL, tokenListNode);
	return (result);
}

t_astree	*TOKENLIST2(void)
{
	return (NULL);
}
