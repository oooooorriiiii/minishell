/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command_struct.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 12:38:26 by sosugimo          #+#    #+#             */
/*   Updated: 2022/02/01 18:18:02 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execute.h"
#include "minishell.h"
#include "utils.h"
#include "msh_error.h"

//	printf("path: %s\n", path);
//	printf("ret: %d\n", ret);
void 	execute_external_cmd(t_cmd_args *args)
{
	char	**env_strs;
	char	*path;
	int		ret;

	env_strs = gen_env_str(g_minishell.env);
	path = add_path(args);
	ret = execve(path, args->cmdpath, env_strs);
	if (ret < 0)
		msh_fatal("execve error: ");
	free_str(&path);
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
	return ;
}
