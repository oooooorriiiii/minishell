/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_visualiver.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 13:53:58 by sosugimo          #+#    #+#             */
/*   Updated: 2022/01/17 14:40:31 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>

#define NODETYPE(a) (a & (~NODE_DATA))

void print_simple_command(ASTreeNode* simple_cmd_node)
{
    printf("@@@@@@@@@@@@@((( simplecmd )))@@@@@@@@@@@@@\n");
	ptrintf("simple_cmd_node : %s\n", simple_cmd_node->szData);
}

void print_command(ASTreeNode* cmdNode)
{
    if (cmdNode == NULL)
        return;

    switch (NODETYPE(cmdNode->type))
    {
    case NODE_REDIRECT_IN:		// right side contains simple cmd node
        printf("@@@@@@@@@@@@@((( cmd : REDIRECT_IN )))@@@@@@@@@@@@@\n");
        print_simple_command(cmdNode->szData);
        break;
    case NODE_REDIRECT_OUT:		// right side contains simple cmd node
        printf("@@@@@@@@@@@@@((( cmd : REDIRECT_OUT )))@@@@@@@@@@@@@\n");
        print_simple_command(cmdNode->szData);
        break;
    case NODE_CMDPATH:
        printf("@@@@@@@@@@@@@((( cmd : CMDPATH )))@@@@@@@@@@@@@\n");
        print_simple_command(NULL);
        break;
    }
}

void print_pipeline(ASTreeNode* t, bool async)
{
    int file_desc[2];

    pipe(file_desc);
    int pipewrite = file_desc[1];
    int piperead = file_desc[0];

	// read input from stdin for the first job
	printf("@@@@@@@@@@@@@@@@@@@@@@ L of PIPENODE @@@@@@@@@@@@@@@@@@@@@@\n");
    print_command(t->left, async, false, true, 0, pipewrite);
    ASTreeNode* jobNode = t->right;

    while (jobNode != NULL && NODETYPE(jobNode->type) == NODE_PIPE)
    {
        printf("@@@@@@@@@@@@@@@@@@@@@@ R of PIPENODE @@@@@@@@@@@@@@@@@@@@@@\n");
        print_command(jobNode->left);
        jobNode = jobNode->right;
    }
	printf("@@@@@@@@@@@@@@@@@@@@@@ R of PIPENODE @@@@@@@@@@@@@@@@@@@@@@\n");
    print_command(jobNode);	// only wait for the last command if necessary
}

void print_job(ASTreeNode* jobNode, bool async)
{
    if (jobNode == NULL)
        return;

    switch (NODETYPE(jobNode->type))
    {
    case NODE_PIPE:
        printf("@@@@@@@@@@@@@((( job : PIPE )))@@@@@@@@@@@@@\n");
        print_pipeline(jobNode, async);
        break;
    case NODE_CMDPATH:
        printf("@@@@@@@@@@@@@((( job : CMD )))@@@@@@@@@@@@@\n");
    default:
        printf("@@@@@@@@@@@@@((( job : default )))@@@@@@@@@@@@@\n");
        print_command(jobNode, async, false, false, 0, 0);
        break;
    }
}

void print_cmdline(ASTreeNode* cmdline)
{
    if (cmdline == NULL)
        return;

    switch(NODETYPE(cmdline->type))
    {
    default:
        printf("@@@@@@@@@@@@@((( cmdline )))@@@@@@@@@@@@@\n");
        print_job(cmdline, false);
    }
}

void print_syntax_tree(ASTreeNode* tree)
{
	// interpret the syntax tree
    print_cmdline(tree);
}
