/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command_struct.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 12:38:26 by sosugimo          #+#    #+#             */
/*   Updated: 2022/01/27 14:28:23 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execute.h"
#include "minishell.h"
#include "utils.h"

void 	execute_external_cmd(t_cmd_args *args)
{
	char	**env_strs;
	int		ret;

	env_strs = gen_env_str(g_minishell.env);
	ret = execve(args->cmdpath[0], args, env_strs);
	if (ret < 0)
	{
		// TODO: handle_execve_error
	}
	free_str_arr(&env_strs);
}

void	execute_command_struct(t_cmd_args *args)
{
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
	else
		execute_external_cmd(args);
	// while (waitpid(pid, NULL, 0) <= 0); //////////////////
	return ;
}
