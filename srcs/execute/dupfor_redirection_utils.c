/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dupfor_redirection_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 09:18:01 by sosugimo          #+#    #+#             */
/*   Updated: 2022/05/15 09:20:34 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execute.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int	simple_error_handle(int status, char *title)
{
	if (status == -1)
	{
		perror(title);
		exit(1);
	}
	return (status);
}

void	connect_pipe(int pipefd[2], int fd)
{
	simple_error_handle(dup2(pipefd[fd], fd), "dup2");
	simple_error_handle(close(pipefd[0]), "close");
	simple_error_handle(close(pipefd[1]), "close");
}
