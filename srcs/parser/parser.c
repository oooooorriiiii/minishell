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

t_astree	*CMDLINE(t_token_list **curtok)
{
	return (JOB(curtok));
}

t_astree	*JOB(t_token_list **curtok)
{
	t_token_list		*save;
	t_astree			*node;

	save = *curtok;
	*curtok = save;
	node = JOB1(curtok);
	if (node != NULL)
		return (node);
	*curtok = save;
	node = JOB2(curtok);
	if (node != NULL)
		return (node);
	return (NULL);
}

/**
* <pipeline> '|' <newline_list> <pipeline>
*/
t_astree	*JOB1(t_token_list **curtok)
{
	t_astree	*cmdNode;
	t_astree	*jobNode;
	t_astree	*result;

	cmdNode = CMD(curtok);
	if (cmdNode == NULL)
		return (NULL);
	if (!term(CHAR_PIPE, NULL, curtok))
	{
		astree_delete(cmdNode);
		return (NULL);
	}
	jobNode = JOB(curtok);
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
t_astree	*JOB2(t_token_list **curtok)
{
	return (CMD(curtok));
}

//--------------------------
#include "../includes/parser.h"
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>


#define NODETYPE(a) (a*1)

void	print_simple_command(t_astree *simple_cmd_node)
{
	t_astree	*node;

	node = simple_cmd_node;
	while (node->szData != NULL)
	{
		printf("		   |\n");
		printf("			-----------simple_cmd_node  :  %s\n", node->szData);
		if (node->right != NULL)
			node = node->right;
		else
			break ;
	}
}

void	print_command(t_astree *cmdNode)
{
	if (cmdNode == NULL)
		return ;
	switch (NODETYPE(cmdNode->type))
	{
		case NODE_REDIRECT_IN:		// <
			printf("	   |\n");
			printf("		-----------< cmd_node >-------  REDIRECT_IN");
			printf("   < %s \n", cmdNode->szData);
			print_simple_command(cmdNode->right);
			break ;
		case NODE_REDIRECT_OUT:		// >
			printf("	   |\n");
			printf("		-----------< cmd_node >-------  REDIRECT_OUT");
			if (cmdNode->szData != NULL)
				printf("   > %s \n", cmdNode->szData);
			print_simple_command(cmdNode->right);
			break ;
		case NODE_REDIRECT_D_IN:		// <<
			printf("	   |\n");
			printf("		-----------< cmd_node >-------  REDIRECT_OUT");
			printf("   << %s \n", cmdNode->szData);
			print_simple_command(cmdNode->right);
			break ;
		case NODE_REDIRECT_D_OUT:		// >>
			printf("	   |\n");
			printf("		-----------< cmd_node >-------  REDIRECT_OUT");
			printf("   >> %s \n", cmdNode->szData);
			print_simple_command(cmdNode->right);
			break ;
		case NODE_CMDPATH:
			printf("	   |\n");
			printf("		-----------< cmd_node >-------  CMDPATH\n");
			print_simple_command(cmdNode);
			break ;
	}
}

void	print_pipeline(t_astree *t, bool async)
{
	t_astree	*jobNode;

	(void)async; // ADDING: ymori
	jobNode = t->right;
	print_command(t->left);
	while (jobNode != NULL && NODETYPE(jobNode->type) == NODE_PIPE)
	{
		printf("   |\n");
		printf("	-----------< job_node >-------  PIPE\n");
		print_command(jobNode->left);
		jobNode = jobNode->right;
	}
	print_command(jobNode);
}

void	print_job(t_astree *jobNode, bool async)
{
	if (jobNode == NULL)
		return ;
	switch (NODETYPE(jobNode->type))
	{
		case NODE_PIPE:
			printf("   |\n");
			printf("	-----------< job_node >-------  PIPE\n");
			print_pipeline(jobNode, async);
			break ;
		case NODE_CMDPATH:
			printf("   |\n");
			printf("	-----------< job_node >-------  CMDPATH\n");
			break ; // ADDING: ymori
		default:
			printf("   |\n");
			printf("	-----------< job_node >-------  default\n");
			print_command(jobNode);
			break ;
	}
}

void	print_cmdline(t_astree *cmdline)
{
	if (cmdline == NULL)
		return ;
	switch (NODETYPE(cmdline->type))
	{
		default:
			printf("-----------< cmdline_node > \n");
			print_job(cmdline, false);
	}
}

void	print_syntax_tree(t_astree *tree)
{
	print_cmdline(tree);
	// astree_delete(tree);
}
//--------------------------

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
	*syntax_tree = CMDLINE(&curtok);
//	printf("Parse\n"); // D
//	print_syntax_tree(*syntax_tree); // DE
//	printf("Parse\n"); // D
	if (curtok != NULL && curtok->type != 0)
	{
		printf("Syntax Error near: %s\n", curtok->val);
		g_minishell.exit_status = 258;
		return (-1);
	}
	return (0);
}
