/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 14:07:57 by sosugimo          #+#    #+#             */
/*   Updated: 2022/01/26 17:04:39 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execute.h"

void	execute_simple_command(t_astree *simple_cmd_node, t_cmd_args *args)
{
	init_command_struct(simple_cmd_node, args);
	execute_command_struct(args);
	destroy_command_struct(args);
}

void	execute_command(t_astree *cmdNode, t_cmd_args *args)
{
	if (cmdNode == NULL)
	{
		// printf("cmdNode == NULL\n");///////
		return ;
	}
	if (cmdNode->type == NODE_REDIRECT_IN)
	{
		args->redirect_in = cmdNode->szData;
		args->redirect_out = NULL;
		execute_simple_command(cmdNode->right, args);
	}
	if (cmdNode->type == NODE_REDIRECT_OUT)
	{
		args->redirect_in = NULL;
		args->redirect_out = cmdNode->szData;
		execute_simple_command(cmdNode->right, args);
	}
	if (cmdNode->type == NODE_CMDPATH)
	{
		args->redirect_in = NULL;
		args->redirect_out = NULL;
		execute_simple_command(cmdNode, args);
	}
}
