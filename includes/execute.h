/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 14:22:04 by sosugimo          #+#    #+#             */
/*   Updated: 2022/01/30 09:58:12 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "../libft/libft.h"
# include "lexer.h"
# include "minishell.h"
# include "parser.h"
# include <stdbool.h>
# include <unistd.h>
# include <stdio.h>

# define STDIN_FILENO 0
# define STDOUT_FILENO 1

# define SINGLE_Q 1
# define DOUBLE_Q 10

typedef struct cmd_args
{
	bool		stdin_pipe;
	bool		stdout_pipe;
	int			pipe_read;
	int			pipe_write;
	char		*redirect_in;
	char		*redirect_out;
	char		*redirect_double_in;
	char		*redirect_double_out;
	int			cmdpath_argc;
	char		**cmdpath;
}				t_cmd_args;

// -----------  execute.c

void			execute_syntax_tree(t_astree *tree);
void			execute_cmdline(t_astree *cmdline, t_cmd_args *args);
void			execute_job(t_astree *jobNode, t_cmd_args *args);
void			execute_pipeline(t_astree *t, t_cmd_args *args);

// -----------  expansion.c

void			extra_strcpy(t_cmd_args *args, t_astree *ast_node);

// -----------  execute_utils.c

int				joudge_process(t_cmd_args *args);
void			execute_simple_command(t_astree *t, t_cmd_args *args);
void			execute_command(t_astree *t, t_cmd_args *args);

// -----------  execute_command_struct.c

void			execute_command_struct(t_cmd_args *args);
int				init_command_struct(t_astree *simplecmdNode, t_cmd_args *args);
void			destroy_command_struct(t_cmd_args *args);

// -----------  init_struct.c

void			init_struct(t_cmd_args *args);

// -----------  parent.c

void			execute_in_parent(t_cmd_args *args);

// -----------  child.c

void			execute_in_child(t_cmd_args *args);

// -----------  execute

void			execute_echo(t_cmd_args *args);
void			execute_cd(t_cmd_args *args);
void			execute_pwd(t_cmd_args *args);
void			execute_export(t_cmd_args *args);
void			execute_unset(t_cmd_args *args);
void			execute_env(t_cmd_args *args);
void			execute_exit(t_cmd_args *args);

#endif
