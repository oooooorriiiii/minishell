/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymori <ymori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 16:11:17 by ymori             #+#    #+#             */
/*   Updated: 2022/05/25 16:11:17 by ymori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/**
 *
 * @param curtok
 * @return
 *
 * < >
 * ::=	'<' <token>
 */
t_astree	*REDIRECTION1(t_token_list **curtok, bool *nofile)
{
	t_astree	*result;
	char		*filename;

	if (!trim_x(curtok, CHAR_LESSER))
		return (NULL);
	if (!trim_alloc(curtok, &filename))
	{
		*nofile = true;
		return (NULL);
	}
	result = malloc(sizeof(*result));
	parse_malloc_errordeal(result, NULL);
	astreeset_type(result, NODE_REDIRECT_IN | ELIGIBLE_EXPANSION);
	astreeset_data(result, filename);
	astree_attach(result, NULL, NULL);
	return (result);
}

/**
 *
 * @param curtok
 * @return
 *
 * < >
 * ::=	'>' <token>
 */
t_astree	*REDIRECTION2(t_token_list **curtok, bool *nofile)
{
	t_astree	*result;
	char		*filename;

	if (!trim_x(curtok, CHAR_GREATER))
		return (NULL);
	if (!trim_alloc(curtok, &filename))
	{
		*nofile = true;
		return (NULL);
	}
	result = malloc(sizeof(*result));
	parse_malloc_errordeal(result, NULL);
	astreeset_type(result, NODE_REDIRECT_OUT | ELIGIBLE_EXPANSION);
	astreeset_data(result, filename);
	astree_attach(result, NULL, NULL);
	return (result);
}

/**
 *
 * @param curtok
 * @return
 *
 * < >
 * ::=	'<<' <token>
 */
t_astree	*REDIRECTION11(t_token_list **curtok, bool *nofile)
{
	t_astree	*result;
	char		*filename;

	if (!trim_x(curtok, CHAR_DBLLESSER))
		return (NULL);
	if (!trim_alloc(curtok, &filename))
	{
		*nofile = true;
		return (NULL);
	}
	result = malloc(sizeof(*result));
	parse_malloc_errordeal(result, NULL);
	astreeset_type(result, NODE_REDIRECT_D_IN | ELIGIBLE_EXPANSION);
	astreeset_data(result, filename);
	astree_attach(result, NULL, NULL);
	return (result);
}

/**
 *
 * @param curtok
 * @return
 *
 * < >
 * ::=	'>>' <token>
 */
t_astree	*REDIRECTION22(t_token_list **curtok, bool *nofile)
{
	t_astree	*result;
	char		*filename;

	if (!trim_x(curtok, CHAR_DBLGREATER))
		return (NULL);
	if (!trim_alloc(curtok, &filename))
	{
		*nofile = true;
		return (NULL);
	}
	result = malloc(sizeof(*result));
	parse_malloc_errordeal(result, NULL);
	astreeset_type(result, NODE_REDIRECT_D_OUT | ELIGIBLE_EXPANSION);
	astreeset_data(result, filename);
	astree_attach(result, NULL, NULL);
	return (result);
}
