/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 16:11:36 by sosugimo          #+#    #+#             */
/*   Updated: 2022/05/14 10:59:59 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	execute_pwd(t_cmd_args *args)
{
	char		cwd[1024];

	(void)args;
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
