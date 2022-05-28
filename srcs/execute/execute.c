/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 16:49:07 by sosugimo          #+#    #+#             */
/*   Updated: 2022/05/15 00:03:41 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execute.h"
#include "msh_signal.h"
#include <wait.h>
#include <errno.h>

void	set_pipefd(t_cmd_args *args, bool stdin_pipe, bool stdout_pipe)
{
	args->stdin_pipe = stdin_pipe;
	args->stdout_pipe = stdout_pipe;
}

//void	execute_pipeline(t_astree *t, t_cmd_args *args)
//{
//	t_astree	*jobNode;
//	int			file_desc[2];
//
//	pipe(file_desc);
//	args->pipe_write = file_desc[1];
//	args->pipe_read = file_desc[0];
//	set_pipefd(args, false, true);
//	execute_command(t->left, args);
//	jobNode = t->right;
//	while (jobNode != NULL && jobNode->type == NODE_PIPE)
//	{
//		close(args->pipe_write);
//		pipe(file_desc);
//		args->pipe_write = file_desc[1];
//		set_pipefd(args, true, true);
//		execute_command(jobNode->left, args);
//		close(args->pipe_read);
//		args->pipe_read = file_desc[0];
//		jobNode = jobNode->right;
//	}
//	args->pipe_read = file_desc[0];
//	close(args->pipe_write);
//	set_pipefd(args, true, false);
//	execute_command(jobNode, args);
//	close(args->pipe_read);
//}

pid_t	execute_pipe(t_astree *astree, t_cmd_args *args)
{
	int		file_desc[2];
	pid_t	pid;

	pipe(file_desc);
	pid = fork();
	if (pid == 0)
	{
		dup2(file_desc[STDOUT_FILENO], STDOUT_FILENO);
		close(file_desc[0]);
		close(file_desc[1]);
		execute_command(astree, args);
		exit(0);
	}
	dup2(file_desc[STDIN_FILENO], STDIN_FILENO);
	close(file_desc[0]);
	close(file_desc[1]);
	return (pid);
}

void
	job_processer(t_astree *jobNode, t_cmd_args *args, pid_t *pid, int *status)
{
	if (jobNode->type & NODE_PIPE)
	{
		*pid = execute_pipe(jobNode->left, args);
		job_processer(jobNode->right, args, pid, status);
	}
	else
	{
		if (*pid == -1 && check_builtin_in_astree(jobNode))
			execute_command(jobNode, args);
		else
		{
			*pid = fork();
			if (*pid == 0)
			{
				execute_command(jobNode, args);
				exit(g_minishell.exit_status);
			}
		}
	}
}

/**
 *
 * @param jobNode
 * @param args
 *
 */
void	execute_job(t_astree *jobNode, t_cmd_args *args, int *status)
{
	pid_t	pid;
	pid_t	wait_pid;
	int		child_status;
	int		fd[2];

	wait_pid = 0;
	pid = -1;
	fd[0] = dup(STDIN_FILENO);
	fd[1] = dup(STDOUT_FILENO);
	signal_init(signal_child_process, signal_child_process, NULL);
	job_processer(jobNode, args, &pid, status);
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
//	if (jobNode == NULL)
//		return ;
//	if (jobNode->type == NODE_PIPE)
//		execute_pipeline(jobNode, args);
//	else if (jobNode->type == NODE_CMDPATH)
//		execute_command(jobNode, args);
//	else
//		execute_command(jobNode, args);
	while (wait_pid >= 0)
	{
		wait_pid = waitpid(-1, &child_status, 0);
		if (wait_pid != -1 && wait_pid == pid)
			*status = child_status;
	}
	if (errno != ECHILD)
	{
		perror("job error");
		exit(1);
	}
	errno = 0;
	signal_init(signal_handler_prompt, SIG_IGN, NULL);
}

void	execute_cmdline(t_astree *cmdline, t_cmd_args *args, int *status)
{
	if (cmdline == NULL)
		return ;
	execute_job(cmdline, args, status);
}

int		get_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (WTERMSIG(status) + 128);
	else if (WIFSTOPPED(status))
		return (WSTOPSIG(status));
	return (1);
}

void	execute_syntax_tree(t_astree *tree)
{
	int			status;
	t_cmd_args	*args;

	args = NULL;
	g_minishell.exit_status = 0;
	status = 0;
	args = (t_cmd_args *)malloc(sizeof(t_cmd_args));
	malloc_error_exec(NULL, NULL, args);
	init_struct(args);
	execute_cmdline(tree, args, &status);
	g_minishell.exit_status = get_status(status);
	free(args);
}
