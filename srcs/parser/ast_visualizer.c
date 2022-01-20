/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_visualizer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 13:53:58 by sosugimo          #+#    #+#             */
/*   Updated: 2022/01/20 14:48:56 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>

#define NODETYPE(a) (a & (~NODE_DATA))

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
	case NODE_REDIRECT_IN:
			printf("	   |\n");
		printf("		-----------< cmd_node >-------  REDIRECT_IN");
		printf("   <   %s \n", cmdNode->szData);
		print_simple_command(cmdNode->right);
		break ;
	case NODE_REDIRECT_OUT:		// right side contains simple cmd node
			printf("	   |\n");
		printf("		-----------< cmd_node >-------  REDIRECT_OUT");
		printf("   >   %s \n", cmdNode->szData);
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
			printf("-----------< cmdline_node >------- \n");
		print_job(cmdline, false);
	}
}

void	print_syntax_tree(t_astree *tree)
{
	print_cmdline(tree);
}
