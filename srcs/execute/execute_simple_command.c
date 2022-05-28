/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 14:07:57 by sosugimo          #+#    #+#             */
/*   Updated: 2022/05/15 09:38:21 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execute.h"
#include "../includes/utils.h"
#include <errno.h>

/**
 *
 * @param cmd
 * @return
 * True: matched with builtin command
 * False:
 */
bool	check_builtin(char *cmd)
{
	if (cmd == NULL)
		return (false);
	if (!ft_strcmp("echo", cmd) || !ft_strcmp("cd", cmd)
		|| !ft_strcmp("pwd", cmd) || !ft_strcmp("export", cmd)
		|| !ft_strcmp("unset", cmd) || !ft_strcmp("exit", cmd)
		|| !ft_strcmp("env", cmd))
		return (true);
	else
		return (false);
}

/**
 *
 * @param astree
 * @return
 */
bool	check_builtin_in_astree(t_astree *astree)
{
	char		*cmd;

	if (astree->type & NODE_REDIRECTION)
		astree = astree->left;
	cmd = astree->szData;
	if (!(astree->type & NODE_CMDPATH))
		return (false);
	if (!ft_strcmp("echo", cmd) || !ft_strcmp("cd", cmd)
		|| !ft_strcmp("pwd", cmd) || !ft_strcmp("export", cmd)
		|| !ft_strcmp("unset", cmd) || !ft_strcmp("exit", cmd)
		|| !ft_strcmp("unset", cmd))
		return (true);
	return (false);
}

/**
 *
 * @param astree
 * @param cmdpath
 * @return
 *  cmdpath pointer
 *  [0]: commant path
 *  [1...]: command arguments
 */
//printf("astree->szData in get_arg: %s\n", astree->szData); // D
char	**get_arg_list(t_astree *astree, t_cmd_args *args)
{
	t_astree	*tmp;
	size_t		i;
	char		**ret;

	tmp = astree;
	i = 0;
	while (tmp)
	{
		tmp = tmp->right;
		i++;
	}
	ret = (char **)malloc(sizeof(char *) * (i + 1));
	args->cmdpath_argc = i;
	i = 0;
	while (astree)
	{
		ret[i] = ft_strdup(astree->szData);
		astree = astree->right;
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

void	execute_builtin(char *cmd, char **arg_list)
{
	(void)arg_list;
	if (!ft_strcmp(cmd, "echo"))
	{
		puts("YA-----------------");
	}
}

void	listprint(char **list) // D
{
	int	i;

	puts("List Print");
	if (list == NULL)
		return ;
	i = 0;
	while (list[i] != NULL)
	{
		printf("[%d]: %s\n", i, list[i]);
		i++;
	}
}

//printf("astree->szData: %s\n", astree->szData); // D
//listprint(args->cmdpath); // D
//printf("args->cmdpath_argc: %d\n", args->cmdpath_argc); // D
void	execute_simplecmd(t_astree *astree, t_cmd_args *args)
{
	char	*path;

	errno = 0;
	args->cmdpath = get_arg_list(astree, args);
	if (check_builtin(args->cmdpath[0]) == false)
	{
		path = add_path(args);
		if (access(path, X_OK) == -1)
			g_minishell.exit_status = 126;
		if (!path)
			g_minishell.exit_status = 127;
		free_str(&path);
	}
	execute_command_struct(args);
	free_str_arr(&args->cmdpath);
}

void	execute_simple_command(t_astree *simple_cmd_node, t_cmd_args *args)
{
	char	*path;

	init_command_struct(simple_cmd_node, args);
	if (!check_builtin(args->cmdpath[0]))
	{
		path = add_path(args);
		if (access(path, X_OK) == -1)
			g_minishell.exit_status = 126;
		if (!path)
			g_minishell.exit_status = 127;
		free_str(&path);
	}
	if (joudge_process(args) == 1)
		execute_in_parent(args);
	else
		execute_in_child(args);
	destroy_command_struct(args);
}

/**
 *
 * @param cmdNode
 * @param args
 *
 */
void	execute_command(t_astree *cmdNode, t_cmd_args *args)
{
	if (cmdNode == NULL)
		return ;
	if (cmdNode->type & NODE_REDIRECTION)
	{
		if (execute_redirection(cmdNode->right, args) == e_failure)
			return ;
		execute_simplecmd(cmdNode->left, args);
	}
	else
		execute_simplecmd(cmdNode, args);
}
