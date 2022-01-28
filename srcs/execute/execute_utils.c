/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 19:23:52 by sosugimo          #+#    #+#             */
/*   Updated: 2022/01/27 21:49:31 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execute.h"

int	joudge_process(t_cmd_args *args)
{
	if (args->pipe_read == true || args->pipe_write == true)
		return (0);
	if (strcmp(args->cmdpath[0], "echo") != 0
		&& strcmp(args->cmdpath[0], "cd") != 0
		&& strcmp(args->cmdpath[0], "pwd") != 0
		&& strcmp(args->cmdpath[0], "export") != 0
		&& strcmp(args->cmdpath[0], "unset") != 0
		&& strcmp(args->cmdpath[0], "env") != 0
		&& strcmp(args->cmdpath[0], "exit") != 0)
		return (0);
	return (1);
}

int	init_command_struct(t_astree *simplecmdNode, t_cmd_args *args)
{
	t_astree	*argNode;
	int			i;

	i = 0;
	if (simplecmdNode == NULL || simplecmdNode->type != NODE_CMDPATH)
	{
		args->cmdpath_argc = 0;
		return (-1);
	}
	argNode = simplecmdNode;
	while (argNode != NULL && (argNode->type == NODE_ARGUMENT
			|| argNode->type == NODE_CMDPATH))
	{
		argNode = argNode->right;
		i++;
	}
	args->cmdpath = (char **)malloc(sizeof(char *) * (i + 1));
	argNode = simplecmdNode;
	extra_strcpy(args, argNode);
	// i = 0;
	// while (argNode != NULL && (argNode->type == NODE_ARGUMENT
	// 		|| argNode->type == NODE_CMDPATH))
	// {
	// 	args->cmdpath[i] = (char *)malloc(strlen(argNode->szData) + 1);
	// 	strcpy(args->cmdpath[i], argNode->szData);////////////////////////
	// 	argNode = argNode->right;
	// 	i++;
	// }
	// args->cmdpath[i] = NULL;
	// args->cmdpath_argc = i;
	return (0);
}

void	destroy_command_struct(t_cmd_args *args)
{
	int	i;

	i = 0;
	while (i < args->cmdpath_argc)
	{
		free(args->cmdpath[i]);
		i++;
	}
	free(args->cmdpath);
	args->cmdpath_argc = 0;
	free(args);
}
