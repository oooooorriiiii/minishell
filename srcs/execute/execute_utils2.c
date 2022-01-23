/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 19:23:52 by sosugimo          #+#    #+#             */
/*   Updated: 2022/01/23 01:53:15 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	execute_command_internal(t_cmd_args *args)
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
	while (waitpid(pid, NULL, 0) <= 0); //////////////////
	return ;
}

int	init_command_internal(t_astree *simplecmdNode, t_cmd_args *args)
{
	t_astree	*argNode;
	int			i;

	i = 0;
	if (simplecmdNode == NULL || simplecmdNode->type != NODE_CMDPATH)
	{
		cmdinternal->argc = 0;
		return (-1);
	}
	argNode = simplecmdNode;
	while (argNode != NULL && argNode->type == NODE_ARGUMENT
		|| argNode->type == NODE_CMDPATH)
	{
		argNode = argNode->right;
		i++;
	}
	args->cmdpath = (char **)malloc(sizeof(char *) * (i + 1));
	argNode = simplecmdNode;
	i = 0;
	while (argNode != NULL && argNode->type == NODE_ARGUMENT
		|| argNode->type == NODE_CMDPATH)
	{
		args->cmdpath[i] = (char *)malloc(strlen(argNode->szData) + 1);
		strcpy(args->cmdpath[i], argNode->szData);
		argNode = argNode->right;
		i++;
	}
	args->cmdpath[i] = NULL;
	args->cmdpath_argc = i;
	return (0);
}
