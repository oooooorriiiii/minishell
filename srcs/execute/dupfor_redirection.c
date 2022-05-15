/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dupfor_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 18:55:12 by sosugimo          #+#    #+#             */
/*   Updated: 2022/05/15 09:18:32 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execute.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// TODO: heredocへの対応
void	open_error_handle(int fd)
{
	if (fd == -1)
	{
		perror("file descripter");
		exit(1);
	}
}

void	handle_heredoc(char *data)
{
	int		pipefd[2];
	pid_t	pid;

	simple_error_handle(pipe(pipefd), "pipe");
	pid = simple_error_handle(fork(), "fork");
	if (pid == 0)
	{
		connect_pipe(pipefd, STDOUT_FILENO);
		simple_error_handle(write(STDOUT_FILENO, data, ft_strlen(data)),
			"write");
		exit(0);
	}
	simple_error_handle(waitpid(pid, NULL, 0), "waitpid");
	connect_pipe(pipefd, STDIN_FILENO);
}

void	dupfor_dbl_redirection(t_cmd_args *args, int *backup)
{
	int	fd;

	fd = 0;
	if (args->redirect_double_in)
	{
		handle_heredoc(args->redirect_double_in);
	}
	if (args->redirect_double_out)
	{
		*backup = dup(STDOUT_FILENO);
		fd = open(args->redirect_double_out, O_WRONLY | O_APPEND);
		open_error_handle(fd);
		dup2(fd, STDOUT_FILENO);
	}
}

void	dupfor_redirection(t_cmd_args *args, int *backup)
{
	int	fd;

	fd = 0;
	if (args->redirect_in)
	{
		*backup = dup(STDIN_FILENO);
		fd = open(args->redirect_in, O_RDONLY);
		open_error_handle(fd);
		dup2(fd, STDIN_FILENO);
	}
	if (args->redirect_out)
	{
		*backup = dup(STDOUT_FILENO);
		fd = open(args->redirect_out, O_WRONLY | O_CREAT | O_TRUNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		open_error_handle(fd);
		dup2(fd, STDOUT_FILENO);
	}
	dupfor_dbl_redirection(args, backup);
}

void	close_fdbackup(t_cmd_args *args, int *backup)
{
	if (args->redirect_in || args->redirect_double_in)
		dup2(*backup, STDIN_FILENO);
	if (args->redirect_out || args->redirect_double_out)
		dup2(*backup, STDOUT_FILENO);
	if (args->redirect_in
		||args->redirect_out || args->redirect_double_out)
		close(*backup);
}
