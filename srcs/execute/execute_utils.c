/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 19:23:52 by sosugimo          #+#    #+#             */
/*   Updated: 2022/02/09 18:15:56 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execute.h"

int	joudge_process(t_cmd_args *args)
{
	if (args->stdin_pipe == true || args->stdout_pipe == true)
		return (0);
	if (args->cmdpath[0] == NULL)
		return (1);
	if (ft_strcmp(args->cmdpath[0], "echo") != 0
		&& ft_strcmp(args->cmdpath[0], "cd") != 0
		&& ft_strcmp(args->cmdpath[0], "pwd") != 0
		&& ft_strcmp(args->cmdpath[0], "export") != 0
		&& ft_strcmp(args->cmdpath[0], "unset") != 0
		&& ft_strcmp(args->cmdpath[0], "env") != 0
		&& ft_strcmp(args->cmdpath[0], "exit") != 0)
		return (0);
	return (1);
}

int	is_need_expansion(t_astree *ast)
{
	int	i;

	i = 0;
	while (ast != NULL && (ast->type == NODE_ARGUMENT
			|| ast->type == NODE_CMDPATH))
	{
		while (ast->szData[i])
		{
			if (ast->szData[i] == '$' || ast->szData[i] == '\''
				|| ast->szData[i] == '\"')
				return (1);
			i++;
		}
		i = 0;
		ast = ast->right;
	}
	return (0);
}

void	just_strcpy(t_cmd_args *args, t_astree *simplecmdNode)
{
	int			i;
	t_astree	*argNode;

	i = 0;
	argNode = simplecmdNode;
	while (argNode != NULL && (argNode->type == NODE_ARGUMENT
			|| argNode->type == NODE_CMDPATH))
	{
		argNode = argNode->right;
		i++;
	}
	args->cmdpath = functional_malloc(i);
	i = 0;
	while (simplecmdNode != NULL && (simplecmdNode->type == NODE_ARGUMENT
			|| simplecmdNode->type == NODE_CMDPATH))
	{
		args->cmdpath[i] = (char *)malloc(strlen(simplecmdNode->szData) + 1);
		malloc_error_exec(args->cmdpath[i], NULL, NULL);
		ft_strlcpy(args->cmdpath[i], simplecmdNode->szData,
			ft_strlen(simplecmdNode->szData) + 1);
		simplecmdNode = simplecmdNode->right;
		i++;
	}
	args->cmdpath[i] = NULL;
	args->cmdpath_argc = i;
}

int	init_command_struct(t_astree *simplecmdNode, t_cmd_args *args)
{
	t_astree	*argNode;
	t_astree	*argNode2;

	if (simplecmdNode == NULL || simplecmdNode->type != NODE_CMDPATH)
	{
		args->cmdpath_argc = 0;
		return (-1);
	}
	argNode = simplecmdNode;
	argNode2 = simplecmdNode;
	if (is_need_expansion(argNode2))
		extra_strcpy(args, argNode);
	else
		just_strcpy(args, argNode);
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
}
