/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 14:22:04 by sosugimo          #+#    #+#             */
/*   Updated: 2022/01/22 19:29:47 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "../libft/libft.h"
# include "../includes/minishell.h"
# include "../includes/parser.h"
# include <stdbool.h>

typedef struct cmd_args
{
	t_astree	*simple_cmd_node;
	bool		stdin_pipe;
	bool		stdout_pipe;
	int			pipe_read;
	int			pipe_write;
	char		*redirect_in;
	char		*redirect_out;
	int			cmdpath_argc;
	char		**cmdpath;
}				t_cmd_args;

// -----------  execute.c

void			execute_syntax_tree(t_astree *tree);
void			execute_cmdline(t_astree *cmdline);
void			execute_job(t_astree *jobNode, t_cmd_args *args);
void			execute_pipeline(t_astree *t, t_cmd_args *args);

// -----------  execute_utils.c

void			execute_simple_command(t_astree *t, t_cmd_args *args);
void			execute_command(t_astree *t, t_cmd_args *args);

// -----------  init_struct.c

t_cmd_args		*init_struct(t_astree	*ast);

#endif
