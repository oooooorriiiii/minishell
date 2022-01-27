/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command_struct.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 12:38:26 by sosugimo          #+#    #+#             */
/*   Updated: 2022/01/27 13:24:59 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	execute_command_struct(t_cmd_args *args)
{
	// dup2で出力先の変更を行う。

	if (args->cmdpath_argc < 0)
		return ;
	if (strcmp(args->cmdpath[0], "echo") == 0)
	{
		execute_echo(args);
		return ;
	}
	else if (strcmp(args->cmdpath[0], "cd") == 0)
	{
		execute_cd(args);
		return ;
	}
	else if (strcmp(args->cmdpath[0], "pwd") == 0)
		return (execute_pwd(args));
	else if (strcmp(args->cmdpath[0], "export") == 0)
	{
		execute_export(args);
		return ;
	}
	else if (strcmp(args->cmdpath[0], "unset") == 0)
	{
		execute_unset(args);
		return ;
	}
	else if (strcmp(args->cmdpath[0], "env") == 0)
	{
		execute_env(args);
		return ;
	}
	else if (strcmp(args->cmdpath[0], "exit") == 0)
	{
		exit(0);
		return ;
	}
	// while (waitpid(pid, NULL, 0) <= 0); //////////////////
	return ;
}
