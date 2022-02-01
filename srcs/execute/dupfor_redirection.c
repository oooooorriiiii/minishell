/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dupfor_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 18:55:12 by sosugimo          #+#    #+#             */
/*   Updated: 2022/01/30 19:42:39 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execute.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void	dupfor_redirection(t_cmd_args *args, int *backup)
{
	int	fd;

	fd = 0;
	if (args->redirect_in)
	{
		*backup = dup(STDIN_FILENO);
		fd = open(args->redirect_in, O_RDONLY);
		dup2(fd, STDIN_FILENO);
	}
	if (args->redirect_out)
	{
		*backup = dup(STDOUT_FILENO);
		fd = open(args->redirect_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(fd, STDOUT_FILENO);
	}
	if (args->redirect_double_in)
	{
		*backup = dup(STDIN_FILENO);
		fd = open(args->redirect_double_in, O_RDONLY);
		dup2(fd, STDIN_FILENO);
	}
	if (args->redirect_double_out)
	{
		*backup = dup(STDOUT_FILENO);
		fd = open(args->redirect_double_out, O_WRONLY | O_APPEND);
		dup2(fd, STDOUT_FILENO);
	}
}

void	close_fdbackup(t_cmd_args *args, int *backup)
{
	if (args->redirect_in || args->redirect_double_in)
		dup2(*backup, STDIN_FILENO);
	if (args->redirect_out || args->redirect_double_out)
		dup2(*backup, STDOUT_FILENO);
	if (args->redirect_in || args->redirect_double_in
		||args->redirect_out || args->redirect_double_out)
		close(*backup);
}
