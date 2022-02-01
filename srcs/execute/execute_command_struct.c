/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command_struct.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 12:38:26 by sosugimo          #+#    #+#             */
/*   Updated: 2022/02/01 18:18:02 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execute.h"
#include "minishell.h"
#include "utils.h"
#include <sys/stat.h>

typedef enum e_cmd_type
{
	ABS,
	REL,
	COM,
}			t_cmd_type;

char	**allocate_mem(const char *str)
{
	size_t	i;
	size_t	split_count;
	char	**ret_str_arr_ptr;

	i = 0;
	split_count = 0;
	while (str[i])
	{
		if (str[i] == ':')
			split_count++;
		i++;
	}
	ret_str_arr_ptr = malloc(sizeof(char *) * (split_count + 2));
	ret_str_arr_ptr[split_count + 1] = NULL;
	return (ret_str_arr_ptr);
}

char	*strdup_elem(char *elem)
{
	char	*ret_str;

	if (!elem)
		return (NULL);
	if (ft_strlen(elem) == 0)
		ret_str = ft_strdup(".");
	else
		ret_str = ft_strdup(elem);
	return (ret_str);
}

char	**get_path_elem_in_envlist(const char *str)
{
	char	**ret_str_arr;
	char	*tmp_str;
	char	*elem_head;
	char	*elem_tail;
	size_t	i;

	i = 0;
	ret_str_arr = allocate_mem(str);
	tmp_str = ft_strdup(str);
	elem_head = tmp_str;
	elem_tail = ft_strchr(elem_head, ':');
	while (elem_tail)
	{
		*elem_tail = '\0';
		ret_str_arr[i] = strdup_elem(elem_head);
		elem_head = elem_tail + 1;
		elem_tail = ft_strchr(elem_head, ':');
		i++;
	}
	ret_str_arr[i] = strdup_elem(elem_head);
	free_str(&tmp_str);
	return (ret_str_arr);
}

char	*get_env_data(const char *key)
{
	t_envlist	*current;
	t_envlist	*envlist;

	envlist = g_minishell.env;
	if (!envlist || !key)
		return (NULL);
	current = envlist;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (!current->value)
				return ("");
			else
				return (current->value);
		}
		current = current->next;
	}
	return ("");
}

t_cmd_type	cmd_type_is(const char *cmd)
{
	if (*cmd == '/')
		return (ABS);
	else if (ft_strchr(cmd, '/'))
		return (REL);
	else
		return (COM);
}

char	*join_path(const char *prev, const char *next)
{
	char	*tmp;
	char	*ret_str;
	size_t	i;

	if (!prev || !next)
		return (NULL);
	tmp = NULL;
	ret_str = NULL;
	tmp = ft_strjoin(prev, "/");
	i = ft_strlen(tmp);
	if (i >= 2 && tmp[i - 2] == '/')
		tmp[i - 1] = '\0';
	ret_str = ft_strjoin(tmp, next);
	free_str(&tmp);
	return (ret_str);
}

bool	is_directory(const char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) == -1)
		return (false);
	if (S_ISDIR(path_stat.st_mode))
		return (true);
	return (false);
}

bool	is_executable(const char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) == -1)
		return (false);
	if ((path_stat.st_mode & S_IXUSR) != S_IXUSR)
		return (false);
	if ((path_stat.st_mode & S_IRUSR) != S_IRUSR)
		return (false);
	return (true);
}

bool	is_cmd_exist(const char *path, char **res)
{
	struct stat	path_stat;

	if (!path)
		return (false);
	if (lstat(path, &path_stat) == -1)
		return (false);
	if (S_ISDIR(path_stat.st_mode))
		return (false);
	free_str(res);
	*res = ft_strdup(path);
	return (true);
}

void	search_cmd(char **path_elems, char **res_str, const char *cmd)
{
	size_t	i;
	char	*path_elem;

	i = 0;
	path_elem = NULL;
	while (path_elems[i])
	{
		free_str(&path_elem);
		path_elem = join_path(path_elems[i], cmd);
		printf("path_elem: %s\n", path_elem);
		if (is_cmd_exist(path_elem, res_str) && !is_directory(path_elem) && is_executable(path_elem))
			break ;
		i++;
	}
	free_str(&path_elem);
}

char	*search_cmd_path(const char *cmd)
{
	char	*ret_str;
	char	**path_elems;
	const char	*env_val = get_env_data("PATH");

	printf("env_val: %s\n", env_val);
	ret_str = NULL;
	if (ft_strcmp((char *)env_val, "") == 0)
	{
		ret_str = ft_strdup(cmd);
		return (ret_str);
	}
	path_elems = get_path_elem_in_envlist(env_val);
	for (int i = 0; path_elems[i] != NULL; i++)
	{
		printf("path_elems[%d] : %s\n", i, path_elems[i]);
	}
	search_cmd(path_elems, &ret_str, cmd);
	free_str_arr(&path_elems);
	return (ret_str);
}

char	*add_path(t_cmd_args *args)
{
	char	*res_str;
	const char	*cmd = args->cmdpath[0];

	if (cmd == NULL)
		return (NULL);
	if (cmd_type_is(cmd) == COM)
		res_str = search_cmd_path(cmd);
	else
		res_str = ft_strdup(cmd);
	printf("ret_str in add_path is : %s\n", res_str);
	return (res_str);
}

void 	execute_external_cmd(t_cmd_args *args)
{
	char	**env_strs;
	char	*path;
	extern char **environ;
	int		ret;

	env_strs = gen_env_str(g_minishell.env);
	path = add_path(args);
	printf("path: %s\n", path);
	ret = execve(path, args->cmdpath, environ); //TODO: remove environ
	printf("ret: %d\n", ret);
	if (ret < 0)
	{
		// TODO: handle_execve_error
	}
	free_str(&path);
	free_str_arr(&env_strs);
}

void	execute_command_struct(t_cmd_args *args)
{
	if (args->cmdpath_argc < 0)
		return ;
	if (strcmp(args->cmdpath[0], "echo") == 0)
	{
		execute_echo(args);
		return ;
	}
	else if (strcmp(args->cmdpath[0], "cd") == 0)
	{
		execute_cd(args);
		return ;
	}
	else if (strcmp(args->cmdpath[0], "pwd") == 0)
		return (execute_pwd(args));
	else if (strcmp(args->cmdpath[0], "export") == 0)
	{
		execute_export(args);
		return ;
	}
	else if (strcmp(args->cmdpath[0], "unset") == 0)
	{
		execute_unset(args);
		return ;
	}
	else if (strcmp(args->cmdpath[0], "env") == 0)
	{
		execute_env(args);
		return ;
	}
	else if (strcmp(args->cmdpath[0], "exit") == 0)
	{
		exit(0);
		return ;
	}
	else
		execute_external_cmd(args);
	return ;
}
