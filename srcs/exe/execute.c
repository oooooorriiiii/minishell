/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 16:49:07 by sosugimo          #+#    #+#             */
/*   Updated: 2022/01/21 17:00:00 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parser.h"
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>

void	execute_simple_command(t_astree *simple_cmd_node,
							 bool async,
							 bool stdin_pipe,
							 bool stdout_pipe,
							 int pipe_read,
							 int pipe_write,
							 char *redirect_in,
							 char *redirect_out
								)
{
	CommandInternal cmdinternal;
	init_command_internal(simple_cmd_node, &cmdinternal, async, stdin_pipe, stdout_pipe,
						  pipe_read, pipe_write, redirect_in, redirect_out
						 );
	execute_command_internal(&cmdinternal);
	destroy_command_internal(&cmdinternal);
}

void	execute_command(t_astree *cmdNode,
							bool async,
							bool stdin_pipe,
							bool stdout_pipe,
							int pipe_read,
							int pipe_write)
{
	if (cmdNode == NULL)
		return ;
	if (cmdNode->type == NODE_REDIRECT_IN)
		execute_simple_command(cmdNode->right,
								async,
								stdin_pipe,
								stdout_pipe,
								pipe_read,
								pipe_write,
								cmdNode->szData, NULL
							  );
	if (cmdNode->type == NODE_REDIRECT_OUT)
		execute_simple_command(cmdNode->right,
								async,
								stdin_pipe,
								stdout_pipe,
								pipe_read,
								pipe_write,
								NULL, cmdNode->szData
							  );
	if (cmdNode->type == NODE_CMDPATH)
		execute_simple_command(cmdNode,
								async,
								stdin_pipe,
								stdout_pipe,
								pipe_read,
								pipe_write,
								NULL, NULL
							  );
}

void	execute_pipeline(t_astree *t, bool async)
{
	t_astree	*jobNode;
	int			file_desc[2];
	int			pipewrite;
	int			piperead;

	pipe(file_desc);
	pipewrite = file_desc[1];
	piperead = file_desc[0];
	execute_command(t->left, async, false, true, 0, pipewrite);
	jobNode = t->right;
	while (jobNode != NULL && NODETYPE(jobNode->type) == NODE_PIPE)
	{
		close(pipewrite);
		pipe(file_desc);
		pipewrite = file_desc[1];
		execute_command(jobNode->left, async, true, true, piperead, pipewrite);
		close(piperead);
		piperead = file_desc[0];
		jobNode = jobNode->right;
	}
	piperead = file_desc[0];
	close(pipewrite);
	execute_command(jobNode, async, true, false, piperead, 0);
	close(piperead);
}

void	execute_job(t_astree *jobNode, bool async)
{
	if (jobNode == NULL)
		return ;
	if (jobNode->type == NODE_PIPE)
		execute_pipeline(jobNode, async);
	else if (jobNode->type == NODE_CMDPATH)
		execute_command(jobNode, async, false, false, 0, 0);
	else
		execute_command(jobNode, async, false, false, 0, 0);
}

void	execute_cmdline(t_astree *cmdline)
{
	if (cmdline == NULL)
		return ;
	execute_job(cmdline, false);
}

void	execute_syntax_tree(t_astree *tree)
{
	execute_cmdline(tree);
}
