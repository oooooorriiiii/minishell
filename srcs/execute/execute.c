/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 16:49:07 by sosugimo          #+#    #+#             */
/*   Updated: 2022/02/05 17:55:47 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execute.h"

void	set_pipefd(t_cmd_args *args, bool stdin_pipe, bool stdout_pipe)
{
	args->stdin_pipe = stdin_pipe;
	args->stdout_pipe = stdout_pipe;
}

void	execute_pipeline(t_astree *t, t_cmd_args *args)
{
	t_astree	*jobNode;
	int			file_desc[2];

	pipe(file_desc);
	args->pipe_write = file_desc[1];
	args->pipe_read = file_desc[0];
	set_pipefd(args, false, true);
	execute_command(t->left, args);
	jobNode = t->right;
	while (jobNode != NULL && jobNode->type == NODE_PIPE)
	{
		close(args->pipe_write);
		pipe(file_desc);
		args->pipe_write = file_desc[1];
		set_pipefd(args, true, true);
		execute_command(jobNode->left, args);
		close(args->pipe_read);
		args->pipe_read = file_desc[0];
		jobNode = jobNode->right;
	}
	args->pipe_read = file_desc[0];
	close(args->pipe_write);
	set_pipefd(args, true, false);
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
		execute_command(jobNode, args);
	else
		execute_command(jobNode, args);
}

void	execute_cmdline(t_astree *cmdline, t_cmd_args *args)
{
	if (cmdline == NULL)
		return ;
	execute_job(cmdline, args);
}

void	execute_syntax_tree(t_astree *tree)
{
	t_cmd_args	*args;

	args = NULL;
	args = (t_cmd_args *)malloc(sizeof(t_cmd_args));
	malloc_error_exec(NULL, NULL, args);
	init_struct(args);
	execute_cmdline(tree, args);
	free(args);
}
