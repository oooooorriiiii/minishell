/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command_struct.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 12:38:26 by sosugimo          #+#    #+#             */
/*   Updated: 2022/05/15 09:37:22 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execute.h"
#include "minishell.h"
#include "utils.h"
#include "msh_error.h"

void	execute_external_cmd(t_cmd_args *args)
{
	char	**env_strs;
	char	*path;
	int		ret;

	if (args->cmdpath[0] == NULL)
	{
		msh_fatal("execve error: ");
		return ;
	}
	env_strs = gen_env_str(g_minishell.env);
	path = add_path(args);
	ret = execve(path, args->cmdpath, env_strs);
	if (ret < 0)
		msh_fatal("execve error: ");
	free_str(&path);
	free_str_arr(&env_strs);
}

void	execute_command_struct2(t_cmd_args *args)
{
	if (ft_strcmp(args->cmdpath[0], "export") == 0)
	{
		execute_export(args);
		return ;
	}
	else if (ft_strcmp(args->cmdpath[0], "unset") == 0)
	{
		execute_unset(args);
		return ;
	}
	else if (ft_strcmp(args->cmdpath[0], "env") == 0)
	{
		execute_env(args);
		return ;
	}
	else if (ft_strcmp(args->cmdpath[0], "exit") == 0)
	{
		execute_exit(args);
		return ;
	}
	return ;
}

//printf("args->cmdpath[0]: %s\n", args->cmdpath[0]); // D
void	execute_command_struct(t_cmd_args *args)
{
//	if (args->cmdpath_argc < 0)
//		return ;
//	else if (args->cmdpath[0] == NULL)
//		execute_external_cmd(args);
	if (ft_strcmp(args->cmdpath[0], "echo") == 0)
	{
		execute_echo(args);
		return ;
	}
	else if (ft_strcmp(args->cmdpath[0], "cd") == 0)
	{
		execute_cd(args);
		return ;
	}
	else if (ft_strcmp(args->cmdpath[0], "pwd") == 0)
		return (execute_pwd(args));
	else if (!ft_strcmp(args->cmdpath[0], "export")
		|| !ft_strcmp(args->cmdpath[0], "unset")
		|| !ft_strcmp(args->cmdpath[0], "env")
		|| !ft_strcmp(args->cmdpath[0], "exit"))
		execute_command_struct2(args);
	else
		execute_external_cmd(args);
	return ;
}

//void	execute_command_struct(char *path)
//{
//	if (path == NULL)
//		return ;
//	else if (args->cmdpath[0] == NULL)
//		execute_external_cmd(args);
//	else if (ft_strcmp(args->cmdpath[0], "echo") == 0)
//	{
//		execute_echo(args);
//		return ;
//	}
//	else if (ft_strcmp(args->cmdpath[0], "cd") == 0)
//	{
//		execute_cd(args);
//		return ;
//	}
//	else if (ft_strcmp(args->cmdpath[0], "pwd") == 0)
//		return (execute_pwd(args));
//	else if (!ft_strcmp(args->cmdpath[0], "export")
//		|| !ft_strcmp(args->cmdpath[0], "unset")
//		|| !ft_strcmp(args->cmdpath[0], "env")
//		|| !ft_strcmp(args->cmdpath[0], "exit"))
//		execute_command_struct2(args);
//	else
//		execute_external_cmd(args);
//	return ;
//}
