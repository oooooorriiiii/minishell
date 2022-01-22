/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 14:07:57 by sosugimo          #+#    #+#             */
/*   Updated: 2022/01/22 14:08:24 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parser.h"

void	execute_simple_command(t_astree *simple_cmd_node,
							 bool async,
							 bool stdin_pipe,
							 bool stdout_pipe,
							 int pipe_read,
							 int pipe_write,
							 char *redirect_in,
							 char *redirect_out
								)
{
	CommandInternal cmdinternal;
	init_command_internal(simple_cmd_node, &cmdinternal, async, stdin_pipe, stdout_pipe,
						  pipe_read, pipe_write, redirect_in, redirect_out
						 );
	execute_command_internal(&cmdinternal);
	destroy_command_internal(&cmdinternal);
}

void	execute_command(t_astree *cmdNode,
							bool async,
							bool stdin_pipe,
							bool stdout_pipe,
							int pipe_read,
							int pipe_write)
{
	if (cmdNode == NULL)
		return ;
	if (cmdNode->type == NODE_REDIRECT_IN)
		execute_simple_command(cmdNode->right,
								async,
								stdin_pipe,
								stdout_pipe,
								pipe_read,
								pipe_write,
								cmdNode->szData, NULL
							  );
	if (cmdNode->type == NODE_REDIRECT_OUT)
		execute_simple_command(cmdNode->right,
								async,
								stdin_pipe,
								stdout_pipe,
								pipe_read,
								pipe_write,
								NULL, cmdNode->szData
							  );
	if (cmdNode->type == NODE_CMDPATH)
		execute_simple_command(cmdNode,
								async,
								stdin_pipe,
								stdout_pipe,
								pipe_read,
								pipe_write,
								NULL, NULL
							  );
}
