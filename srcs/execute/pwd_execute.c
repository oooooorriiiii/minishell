/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 16:11:36 by sosugimo          #+#    #+#             */
/*   Updated: 2022/01/27 14:40:36 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execute.h"

void	execute_pwd(t_cmd_args *args)
{
	pid_t		pid;
	pid_t		wait;
	int			fd;
	char		cwd[1024];

	// pid = fork();
	// if (pid == 0 )
	// {
		if (args->redirect_out)
		{
			fd = open(args->redirect_out, O_WRONLY | O_CREAT | O_TRUNC,
					S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
			if (fd == -1)
			{
				perror(args->redirect_out);
				exit(1);
			}
			dup2(fd, STDOUT_FILENO);
		}
		if (args->stdout_pipe)
			dup2(args->pipe_write, STDOUT_FILENO);
		if (getcwd(cwd, sizeof(cwd)) != NULL)
			fprintf(stdout, "%s\n", cwd);
		else
			perror("getcwd() error");
		exit(0);
	// }
	// else if (pid < 0)
	// {
	// 	perror("fork");
	// 	return ;
	// }
	// else
	// {
	// 	wait = waitpid(pid, NULL, 0);
	// 	while (wait <= 0)
	// 		wait = waitpid(pid, NULL, 0);
	// }
	return ;
}
