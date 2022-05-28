/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 12:24:41 by sosugimo          #+#    #+#             */
/*   Updated: 2022/02/05 12:36:07 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

t_astree	*CMDLINE(t_token_list **curtok, bool *nofile)
{
	return (JOB(curtok, nofile));
}

t_astree	*JOB(t_token_list **curtok, bool *nofile)
{
	t_token_list		*save;
	t_astree			*node;

	save = *curtok;
	*curtok = save;
	node = JOB1(curtok, nofile);
	if (node != NULL)
		return (node);
	*curtok = save;
	node = JOB2(curtok, nofile);
	if (node != NULL)
		return (node);
	return (NULL);
}

/**
* <pipeline> '|' <newline_list> <pipeline>
*/
t_astree	*JOB1(t_token_list **curtok, bool *nofile)
{
	t_astree	*cmdNode;
	t_astree	*jobNode;
	t_astree	*result;

	cmdNode = CMD(curtok, nofile);
	if (cmdNode == NULL)
		return (NULL);
	if (!term(CHAR_PIPE, NULL, curtok))
	{
		astree_delete(cmdNode);
		return (NULL);
	}
	jobNode = JOB(curtok, nofile);
	if (jobNode == NULL)
	{
		astree_delete(cmdNode);
		return (NULL);
	}
	result = malloc(sizeof(*result));
	parse_malloc_errordeal(result, NULL);
	astreeset_type(result, NODE_PIPE);
	astree_attach(result, cmdNode, jobNode);
	return (result);
}

/**
 *
 * @param curtok
 * @return
 *
 * <command>
 */
t_astree	*JOB2(t_token_list **curtok, bool *nofile)
{
	return (CMD(curtok, nofile));
}

/**
 * -------------------------------------------------------------------
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
 * --------------------------------------------------------------------
 *
 * <token> ::= <letter> | <token> <letter>
 *
 * TOKENLIST
 * <token list> ::= <token> <token list> -> TOKENLIST1
 *                | <EMPTY>              -> TOKENLIST2
 *
 * <pathname> ::= <token>
 *
 * REDIRECTION_LIST
 * <redirection list> ::= <redirection> <redirection list> -> REDIRECTION_LIST1
 *
 * REDIRECTION
 * <redirection> ::= '>'  <token> -> REDIRECTION1
 *                 | '<'  <token> -> REDIRECTION2
 *                 | '>>' <token> -> REDIRECTION3
 *                 | '<<' <token> -> REDIRECTION4
 *
 * CMD
 * <command> ::= <simple command> <command>   -> COMMAND1
 *             | <redirection list> <command> -> COMMAND2
 *             | <EMPTY>                      -> COMMAND3
 *
 *
 * <newline_list> ::=
 *                  | <newline_list> '\n'
 *
 * JOB
 * <pipeline> ::= <pipeline> '|' <newline_list> <pipeline> -> JOB1
 *              | <command>                                -> JOB2
 *
 * **Node type**
 * NODE_PIPE
 * NODE_REDIRECTION_IN
 * NODE_REDIRECTION_OUT
 * NODE_REDIRECTION_D_IN
 * NODE_REDIRECTION_D_OUT
 * NODE_CMDPATH
 * NODE_ARGUMENT
 */
int	parse(t_lexer *lexbuf, t_astree **syntax_tree)
{
	t_token_list	*curtok;
	bool			nofile;

	nofile = false;
	if (lexbuf == NULL)
	{
		printf("error: lexbuf == NULL\n");
		g_minishell.exit_status = 258;
		return (-1);
	}
	if (lexbuf->len == 0)
	{
		printf("error: lexbuf->len == 0");
		g_minishell.exit_status = 258;
		return (-1);
	}
	curtok = lexbuf->list;
	*syntax_tree = CMDLINE(&curtok, &nofile);
	if ((curtok != NULL && curtok->type != 0) || nofile == true)
	{
		ft_putstr_fd("syntax error\n", STDERR_FILENO);
		g_minishell.exit_status = 258;
		return (-1);
	}
	return (0);
}
