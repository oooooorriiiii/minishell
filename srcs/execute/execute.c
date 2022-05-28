/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 16:49:07 by sosugimo          #+#    #+#             */
/*   Updated: 2022/05/15 00:03:41 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execute.h"

void	set_pipefd(t_cmd_args *args, bool stdin_pipe, bool stdout_pipe)
{
	args->stdin_pipe = stdin_pipe;
	args->stdout_pipe = stdout_pipe;
}

void	execute_cmdline(t_astree *cmdline, t_cmd_args *args, int *status)
{
	if (cmdline == NULL)
		return ;
	execute_job(cmdline, args, status);
}

void	execute_syntax_tree(t_astree *tree)
{
	int			status;
	t_cmd_args	*args;

	args = NULL;
	g_minishell.exit_status = 0;
	status = 0;
	args = (t_cmd_args *)malloc(sizeof(t_cmd_args));
	malloc_error_exec(NULL, NULL, args);
	init_struct(args);
	execute_cmdline(tree, args, &status);
	g_minishell.exit_status = get_exit_status(status);
	free(args);
}
