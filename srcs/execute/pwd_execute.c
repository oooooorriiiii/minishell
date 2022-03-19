/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 16:11:36 by sosugimo          #+#    #+#             */
/*   Updated: 2022/02/04 20:00:10 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execute.h"

void	execute_pwd(t_cmd_args *args)
{
//	pid_t		pid; // ymori
//	pid_t		wait;
//	int			fd;
	char		cwd[1024];

	(void)args; // ADD: ymori
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("%s\n", cwd);
		g_minishell.exit_status = 0;
	}
	else
	{
		perror("getcwd() error");
		g_minishell.exit_status = 1;
	}
	return ;
}
