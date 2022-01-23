/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 16:49:07 by sosugimo          #+#    #+#             */
/*   Updated: 2022/01/22 19:06:56 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>

void	execute_pipeline(t_astree *t, t_cmd_args *args)
{
	t_astree	*jobNode;
	int			file_desc[2];

	pipe(file_desc);
	args->pipe_write = file_desc[1];
	args->pipe_read = file_desc[0];
	args->stdin_pipe = false;
	args->stdout_pipe = true;
	execute_command(t->left, args);
	jobNode = t->right;
	while (jobNode != NULL && jobNode->type == NODE_PIPE)
	{
		close(args->pipe_write);
		pipe(file_desc);
		args->pipe_write = file_desc[1];
		args->stdin_pipe = true;
		args->stdout_pipe = true;
		execute_command(jobNode->left, args);
		close(args->pipe_read);
		args->pipe_read = file_desc[0];
		jobNode = jobNode->right;
	}
	args->pipe_read = file_desc[0];
	close(args->pipe_write);
	args->stdin_pipe = true;
	args->stdout_pipe = false;
	execute_command(jobNode, args);
	close(args->pipe_read);
}

void	execute_job(t_astree *jobNode, t_cmd_args *args)
{
	if (jobNode == NULL)
		return ;
	if (jobNode->type == NODE_PIPE)
		execute_pipeline(jobNode, args);
	else if (jobNode->type == NODE_CMDPATH)
		execute_command(args);
	else
		execute_command(args);
}

void	execute_cmdline(t_astree *cmdline, t_cmd_args *args)
{
	if (cmdline == NULL)
		return ;
	execute_job(cmdline, false);
}

void	execute_syntax_tree(t_astree *tree)
{
	t_cmd_args	*args;

	args = init_struct;
	execute_cmdline(tree);
}
