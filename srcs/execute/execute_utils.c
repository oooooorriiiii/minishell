/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 19:23:52 by sosugimo          #+#    #+#             */
/*   Updated: 2022/02/03 00:33:50 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execute.h"

void	print_allstruct(t_cmd_args *args)
{
	int			i;
	t_cmd_args	*tmp;

	i = 0;
	tmp = NULL;
	printf("/////////////////////  print_allstruct ///////////////////////\n");
	if (args->stdin_pipe == true)
		printf("stdin_pipe :   true    /    ");
	else
		printf("stdin_pipe :   false    /    ");
	if (args->stdout_pipe == true)
		printf("stdout_pipe :   true\n");
	else
		printf("stdout_pipe :   false\n");
	printf("pipe_read :   %d   /   pipe_write :   %d\n", args->pipe_read, args->pipe_write);
	if (args->redirect_in)
		printf("redirect_in :   %s\n", args->redirect_in);
	else
		printf("redirect_in :   NONE\n");
	if (args->redirect_out)
		printf("redirect_out :   %s\n", args->redirect_in);
	else
		printf("redirect_out :   NONE\n");
	if (args->redirect_double_in)
		printf("redirect_double_in :   %s\n", args->redirect_double_in);
	if (args->redirect_double_out)
		printf("redirect_double_out :   %s\n", args->redirect_double_in);
	printf("cmdpath_argc  :    %d\n", args->cmdpath_argc);
	tmp = args;
	while (tmp->cmdpath[i])
	{
		printf("cmdpath[%d] :   %s\n", i, tmp->cmdpath[i]);
		i++;
	}
	printf("/////////////////////////////////////////////////////////////\n");
}

int	joudge_process(t_cmd_args *args)
{
	if (args->stdin_pipe == true || args->stdout_pipe == true)
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
	args->cmdpath = (char **)malloc(sizeof(char *) * (i + 1));
	malloc_error_exec(NULL, args->cmdpath, NULL);
	i = 0;
	while (simplecmdNode != NULL && (simplecmdNode->type == NODE_ARGUMENT
			|| simplecmdNode->type == NODE_CMDPATH))
	{
		args->cmdpath[i] = (char *)malloc(strlen(simplecmdNode->szData) + 1);
		malloc_error_exec(args->cmdpath[i], NULL, NULL);
		strcpy(args->cmdpath[i], simplecmdNode->szData);////////////////////////
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
	int			i;

	i = 0;
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
