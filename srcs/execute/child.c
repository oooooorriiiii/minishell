/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 12:43:47 by sosugimo          #+#    #+#             */
/*   Updated: 2022/01/27 16:11:44 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execute.h"

void	execute_in_child(t_cmd_args *args)
{
	pid_t	pid;
	int		fd;

	pid = fork();
	if (pid < 0)
		exit(0);// error
	if (pid == 0)
	{
		if (args->redirect_out)
		{
			fd = open(args->redirect_out, O_WRONLY);
			dup2(fd, STDOUT_FILENO);
		}
		if (args->redirect_in)
		{
			fd = open(args->redirect_in, O_WRONLY);
			dup2(fd, STDIN_FILENO);
		}
		if (args->pipe_read)
			dup2(args->pipe_read, STDIN_FILENO);
		if (args->pipe_write)
			dup2(args->pipe_write, STDOUT_FILENO);
		execute_command_struct(args);
	}
	close(args->pipe_read);
	close(args->pipe_write);
}

/*
void	execute_in_child(t_cmd_args *args)
{
	pid_t	pid;
	int		new_pipe[2];

	create_pipe(state, new_pipe);
	if ((pid = fork()) < 0)
		error_exit(NULL);
	if (pid == 0)
	{
		set_signal_handler(SIG_DFL);
		if (setup_redirects(command) == FALSE)
			exit(EXIT_FAILURE);
		if (args[0] == NULL)
			exit(EXIT_SUCCESS);
		dup_pipe(state, old_pipe, new_pipe);
		if (dup_redirects(command, FALSE) == FALSE)
			exit(EXIT_FAILURE);
		if (is_builtin(args))
			exit(exec_builtin(args));
		else
			exec_binary(args);
	}
	set_signal_handler(SIG_IGN);
	cleanup_pipe(state, old_pipe, new_pipe);
	command->pid = pid;
}
*/
