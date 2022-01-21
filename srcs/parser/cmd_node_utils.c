/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_node_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 18:55:29 by sosugimo          #+#    #+#             */
/*   Updated: 2022/01/21 15:53:13 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

t_astree	*CMD11(t_token_list **curtok)
{
	t_astree	*simplecmdNode;
	t_astree	*result;
	char		*filename;

	simplecmdNode = SIMPLECMD(curtok);
	if (simplecmdNode == NULL)
		return (NULL);
	if (!term(CHAR_DBLLESSER, NULL, curtok))
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
	astreeset_type(result, NODE_REDIRECT_D_IN);
	astreeset_data(result, filename);
	astree_attach(result, NULL, simplecmdNode);
	return (result);
}

t_astree	*CMD22(t_token_list **curtok)
{
	t_astree	*simplecmdNode;
	t_astree	*result;
	char		*filename;

	simplecmdNode = SIMPLECMD(curtok);
	if (simplecmdNode == NULL)
		return (NULL);
	if (!term(CHAR_DBLGREATER, NULL, curtok))
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
	astreeset_type(result, NODE_REDIRECT_D_OUT);
	astreeset_data(result, filename);
	astree_attach(result, NULL, simplecmdNode);
	return (result);
}
