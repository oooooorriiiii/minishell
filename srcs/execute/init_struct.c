/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 18:23:25 by sosugimo          #+#    #+#             */
/*   Updated: 2022/01/31 10:13:02 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execute.h"

void	init_struct(t_cmd_args *args)
{
	args->stdin_pipe = false;
	args->stdout_pipe = false;
	args->pipe_read = 0;
	args->pipe_write = 0;
	args->redirect_in = NULL;
	args->redirect_out = NULL;
	args->redirect_double_in = NULL;
	args->redirect_double_out = NULL;
	args->cmdpath = NULL;
	args->cmdpath_argc = 0;
}
