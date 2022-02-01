/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 12:43:47 by sosugimo          #+#    #+#             */
/*   Updated: 2022/02/01 18:17:29 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execute.h"

void	execute_in_child(t_cmd_args *args)
{
	pid_t	pid;
	pid_t	wait_pid;
	int		backup;

	backup = 0;
	pid = fork();
	if (pid < 0)
		exit(0);
	else if (pid == 0)
	{
		if (args->pipe_read)
			dup2(args->pipe_read, STDIN_FILENO);
		if (args->pipe_write)
			dup2(args->pipe_write, STDOUT_FILENO);
		dupfor_redirection(args, &backup);
		execute_command_struct(args);
		close_fdbackup(args, &backup);
	}
	else
	{
		wait_pid = waitpid(pid, NULL, 0);
		while (wait_pid <= 0)
			wait_pid = waitpid(pid, NULL, 0);
	}
}
