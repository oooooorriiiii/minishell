/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 12:43:47 by sosugimo          #+#    #+#             */
/*   Updated: 2022/01/27 12:45:26 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static void	exec_command_child(
	t_command *command, char **args, t_pipe_state state, int old_pipe[])
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
