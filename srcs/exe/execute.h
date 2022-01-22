/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 14:22:04 by sosugimo          #+#    #+#             */
/*   Updated: 2022/01/22 14:26:17 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "../libft/libft.h"
# include "../includes/minishell.h"
# include <stdbool.h>

typedef struct cmd_args
{
	t_astree	*simple_cmd_node;
	bool		async;
	bool		stdin_pipe;
	bool		stdout_pipe;
	int			pipe_read;
	int			pipe_write;
	char		*redirect_in;
	char		*redirect_out;
}				t_cmd_args;

void			execute_syntax_tree(t_astree *tree);
void			execute_cmdline(t_astree *cmdline);
void			execute_job(t_astree *jobNode, bool async);
void			execute_pipeline(t_astree *t, bool async);

#endif
