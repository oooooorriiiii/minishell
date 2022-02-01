/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 16:11:36 by sosugimo          #+#    #+#             */
/*   Updated: 2022/02/01 14:39:06 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execute.h"

void	execute_pwd(t_cmd_args *args)
{
	pid_t		pid;
	pid_t		wait;
	int			fd;
	char		cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		fprintf(stdout, "%s\n", cwd);
	else
		perror("getcwd() error");
	// exit(0);
	return ;
}
