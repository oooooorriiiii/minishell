/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 16:11:36 by sosugimo          #+#    #+#             */
/*   Updated: 2022/02/04 17:42:27 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execute.h"

void	execute_pwd(t_cmd_args *args)
{
	pid_t		pid;
	pid_t		wait;
	int			fd;
	char		cwd[1024];

	if (args->cmdpath_argc > 1)
		printf("pwd: too many arguments\n");
	else if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
		perror("getcwd() error");
	return ;
}
