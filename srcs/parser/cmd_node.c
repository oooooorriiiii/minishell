/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 12:37:31 by sosugimo          #+#    #+#             */
/*   Updated: 2022/01/21 15:58:39 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

t_astree	*CMD(t_token_list **curtok)
{
	t_token_list		*save;
	t_astree			*node;

	save = *curtok;
	*curtok = save;
	printf(" ----------[ CMD 1 ]----------\n");
	node = CMD1(curtok);
	if (node != NULL)
		return (node);
	*curtok = save;
	printf(" ----------[ CMD 2 ]----------\n");
	node = CMD2(curtok);
	if (node != NULL)
		return (node);
	*curtok = save;
	printf(" ----------[ CMD 11 ]----------\n");
	node = CMD11(curtok);
	if (node != NULL)
		return (node);
	*curtok = save;
	printf(" ----------[ CMD 22 ]----------\n");
	node = CMD22(curtok);
	if (node != NULL)
		return (node);
	*curtok = save;
	printf(" ----------[ CMD 3 ]----------\n");
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
	if ((*curtok) != NULL)
		printf("%s (*curtok)->type :  %d  == toketype :  %d\n",(*curtok)->val, (*curtok)->type, CHAR_GREATER);
	printf("-----------------------------@@@@@@@@@@@@@@@@@@@ \n");
	if (!term(CHAR_GREATER, NULL, curtok))
	{
		printf("----------- ###################\n");
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
	astreeset_type(result, NODE_REDIRECT_OUT);
	astreeset_data(result, filename);
	astree_attach(result, NULL, simplecmdNode);
	return (result);
}

t_astree	*CMD3(t_token_list **curtok)
{
	return (SIMPLECMD(curtok));
}
