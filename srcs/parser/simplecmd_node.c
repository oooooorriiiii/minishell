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

/*
* <letter> ::= a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z|
 *              A|B|C|D|E|F|G|H|I|J|K|L|M|N|O|P|Q|R|S|T|U|V|W|X|Y|Z
 *
 * <digit> ::= 0|1|2|3|4|5|6|7|8|9
 *
 * <number> ::= <digit>
 *            | <number> <digit>
 *
 * <word> ::= <letter>        -> TOKENLIST1
 *          | <word> <letter> -> TOKENLIST1
 *          | <word> '_'      -> TOKENLIST1
 *
 * <assignment_word> ::= <word> '=' <word> // Handled by other functions
 *
 * <redirection> ::= '>' <word>
 *                 | '<' <word>
 *                 | '>>' <word>
 *                 | '<<' <word>
 *
 * // CMD3, SIMPLECMD, SIMPLECMD1
 * <simple_command_element> ::= <word>            -> TOKENLIST
 *                            | <assignment_word> // Handled by other functions
 *                            | <redirection>
 */
t_astree	*SIMPLECMD(t_token_list **curtok)
{
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
	// REDIRECTION
	result = malloc(sizeof(t_astree));
	parse_malloc_errordeal(result, NULL);
	astreeset_type(result, NODE_CMDPATH);
	astreeset_data(result, pathname);
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
	(void)curtok;
	return (NULL);
}
