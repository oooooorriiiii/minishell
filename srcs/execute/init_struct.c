/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 18:23:25 by sosugimo          #+#    #+#             */
/*   Updated: 2022/01/22 19:29:32 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

t_cmd_args	*init_struct(t_astree	*ast)
{
	t_cmd_args	*args;

	args = (t_cmd_args *)malloc(sizeof(t_cmd_args *));
	args->simple_cmd_node = ast;
	args->stdin_pipe = false;
	args->stdout_pipe = false;
	args->pipe_read = 0;
	args->pipe_write = 0;
	args->redirect_in = NULL;
	args->redirect_out = NULL;
	args->cmdpath_argc = NULL;
	args->cmdpath = NULL;
}
