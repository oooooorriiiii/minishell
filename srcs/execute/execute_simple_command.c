/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 14:07:57 by sosugimo          #+#    #+#             */
/*   Updated: 2022/02/07 21:23:57 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execute.h"

bool	check_builtin(char *cmd)
{
	if (!strcmp("echo", cmd) || !strcmp("cd", cmd) || !strcmp("pwd", cmd)
		|| !strcmp("export", cmd) || !strcmp("unset", cmd)
		|| !strcmp("exit", cmd))
		return (true);
	else
		return (false);
}

void	execute_simple_command(t_astree *simple_cmd_node, t_cmd_args *args)
{
	char	*path;

	init_command_struct(simple_cmd_node, args);
	// print_allstruct(args);
	if (!check_builtin(args->cmdpath[0]))
	{
		path = add_path(args);
		if (access(path, X_OK) == -1)
			g_minishell.exit_status = 126;
		if (!path)
			g_minishell.exit_status = 127;
	}
	if (joudge_process(args) == 1)
		execute_in_parent(args);
	else
		execute_in_child(args);
	destroy_command_struct(args);
}

void	execute_command(t_astree *cmdNode, t_cmd_args *args)
{
	if (cmdNode == NULL)
		return ;
	if (cmdNode->type == NODE_REDIRECT_IN)
	{
		args->redirect_in = cmdNode->szData;
		execute_simple_command(cmdNode->right, args);
	}
	if (cmdNode->type == NODE_REDIRECT_OUT)
	{
		args->redirect_out = cmdNode->szData;
		execute_simple_command(cmdNode->right, args);
	}
	if (cmdNode->type == NODE_REDIRECT_D_IN)
	{
		args->redirect_double_in = cmdNode->szData;
		execute_simple_command(cmdNode->right, args);
	}
	if (cmdNode->type == NODE_REDIRECT_D_OUT)
	{
		args->redirect_double_out = cmdNode->szData;
		execute_simple_command(cmdNode->right, args);
	}
	if (cmdNode->type == NODE_CMDPATH)
		execute_simple_command(cmdNode, args);
}
