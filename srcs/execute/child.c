/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 12:43:47 by sosugimo          #+#    #+#             */
/*   Updated: 2022/05/14 11:01:24 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execute.h"
#include "minishell.h"
#include "utils.h"
#include "msh_error.h"
#include <sys/wait.h>

static void	handle_command_status(int status, bool catch_sigint)
{
	int			signal;

	if (g_minishell.exit_status != 127 && g_minishell.exit_status != 126)
	{
		if (WIFEXITED(status))
			g_minishell.exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			signal = WTERMSIG(status);
			if (signal == SIGQUIT)
				ft_putendl_fd("Quit: 3", STDERR_FILENO);
			g_minishell.exit_status = signal + 128;
			printf("g_minishell.exit_status :  %d\n", g_minishell.exit_status);
		}
		if (catch_sigint)
			ft_putendl_fd("", STDERR_FILENO);
	}
}

/*
void	wait_commands(t_command *command)
{
	extern int	g_status;
	int			status;
	t_bool		has_child;
	t_bool		catch_sigint;

	has_child = FALSE;
	catch_sigint = FALSE;
	while (command)
	{
		if (command->pid != NO_PID)
		{
			if (waitpid(command->pid, &status, 0) < 0)
				error_exit(NULL);
			if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
				catch_sigint = TRUE;
			has_child = TRUE;
		}
		command = command->next;
	}
	if (has_child == FALSE)
		return ;
	handle_command_status(status, catch_sigint);
}
*/

void	execute_in_child(t_cmd_args *args)
{
	pid_t	pid;
	int		backup;
	int		status;

	backup = 0;
	pid = fork();
	if (pid < 0)
		exit(0);
	else if (pid == 0)
	{
		if (args->stdin_pipe)
			dup2(args->pipe_read, STDIN_FILENO);
		if (args->stdout_pipe)
			dup2(args->pipe_write, STDOUT_FILENO);
		dupfor_redirection(args, &backup);
		execute_command_struct(args);
		close_fdbackup(args, &backup);
		exit(0);
	}
	else
		wait(&status);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		handle_command_status(status, true);
	else
		handle_command_status(status, false);
}
