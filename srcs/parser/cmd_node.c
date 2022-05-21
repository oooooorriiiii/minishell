/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 12:37:31 by sosugimo          #+#    #+#             */
/*   Updated: 2022/02/05 17:57:29 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

/*
 * current
 * <CMD>
 * ::=  <simple commant> '<'  <token(file name)> -> CMD1
 * |    <simple commant> '>'  <token(file name)> -> CMD2
 * |    <simple commant> '<<' <token(file name)> -> CMD11
 * |    <simple commant> '<<' <token(file name)> -> CMD22
 * |    <simple commant>                         -> CMD3
 *
 * <CMD>              ::=  <redirection list> <CMD>
 * <redirection list> ::=  <redirection> <redirection list>
 * <redirection>      ::=  '<'  <token(file name)>
 *                    |    '>'  <token(file name)>
 *                    |    '<<' <token(file name)>
 *                    |    '<<' <token(file name)>
 *
 * <letter> ::= a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z|
 *              A|B|C|D|E|F|G|H|I|J|K|L|M|N|O|P|Q|R|S|T|U|V|W|X|Y|Z
 *
 * <digit> ::= 0|1|2|3|4|5|6|7|8|9
 *
 * <number> ::= <digit>
 *            | <number> <digit>
 *
 * <word> ::= <letter>
 *          | <word> <letter>
 *          | <word> '_'
 *
 * <assignment_word> ::= <word> '=' <word> // Handled by other functions
 *
 * <redirection> ::= '>' <word>  -> CMD1
 *                 | '<' <word>  -> CMD2
 *                 | '>>' <word>  -> CMD11
 *                 | '<<' <word>  -> CMD22
 *
 * // CMD3, SIMPLECMD, SIMPLECMD1
 * <simple_command_element> ::= <word> ->
 *                            | <assignment_word> // Handled by other functions
 *                            | <redirection>
 *
 * <redirection_list> ::= <redirection>
 *                      | <redirection_list> <redirection>
 * // CMD
 * <simple_command> ::= <simple_command_element>
 *                    | <simple_command> <simple_command_element>
 *
 * // CMD
 * <command> ::= <simple_command> ::= <simple_command_element>
 *           ::= <word>        ->
 *             | <redirection_list> -> REDIRECTION_LIST
 */
t_astree	*CMD(t_token_list **curtok)
{
	return (CMD3(curtok));
//	t_token_list		*save;
//	t_astree			*node;
//
//	save = *curtok;
//	*curtok = save;
//	node = CMD1(curtok);
//	if (node != NULL)
//		return (node);
//	*curtok = save;
//	node = CMD2(curtok);
//	if (node != NULL)
//		return (node);
//	*curtok = save;
//	node = CMD11(curtok);
//	if (node != NULL)
//		return (node);
//	*curtok = save;
//	node = CMD22(curtok);
//	if (node != NULL)
//		return (node);
//	*curtok = save;
//	node = CMD3(curtok);
//	if (node != NULL)
//		return (node);
//	return (NULL);
}

/*
 * current
 * < >
 * ::=	<simple command> '<' <token>
 */
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
		astree_delete(simplecmdNode);
		return (NULL);
	}
	result = malloc(sizeof(*result));
	parse_malloc_errordeal(result, NULL);
	astreeset_type(result, NODE_REDIRECT_IN);
	astreeset_data(result, filename);
	astree_attach(result, NULL, simplecmdNode);
	return (result);
}

/*
 * < >
 * ::=	<simple command> '>' <token>
 */
t_astree	*CMD2(t_token_list **curtok)
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
		astree_delete(simplecmdNode);
		return (NULL);
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
