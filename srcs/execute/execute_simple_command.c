/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 14:07:57 by sosugimo          #+#    #+#             */
/*   Updated: 2022/01/29 20:06:42 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execute.h"

void	execute_simple_command(t_astree *simple_cmd_node, t_cmd_args *args)
{
	init_command_struct(simple_cmd_node, args);
	if (joudge_process(args) == 1)
		execute_in_parent(args);
	else
		execute_in_child(args);
	// execute_command_struct(args);
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
