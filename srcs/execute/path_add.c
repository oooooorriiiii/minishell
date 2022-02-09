/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_add.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 15:40:50 by ymori             #+#    #+#             */
/*   Updated: 2022/02/06 00:25:09 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "utils.h"

typedef enum e_cmd_type
{
	ABS,
	REL,
	COM,
}			t_cmd_type;

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

//		printf("path_elem: %s\n", path_elem);
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
		if (is_cmd_exist(path_elem, res_str) && \
				!is_directory(path_elem) && is_executable(path_elem))
			break ;
		i++;
	}
	free_str(&path_elem);
}

//	printf("env_val: %s\n", env_val);
//	for (int i = 0; path_elems[i] != NULL; i++)
//	{
//		printf("path_elems[%d] : %s\n", i, path_elems[i]);
//	}
char	*search_cmd_path(const char *cmd)
{
	char		*ret_str;
	char		**path_elems;
	const char	*env_val = get_env_value("PATH");

	ret_str = NULL;
	if (ft_strcmp((char *)env_val, "") == 0)
	{
		ret_str = ft_strdup(cmd);
		return (ret_str);
	}
	path_elems = get_path_elem_in_envlist(env_val);
	search_cmd(path_elems, &ret_str, cmd);
	free_str_arr(&path_elems);
	return (ret_str);
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

// printf("ret_str in add_path is : %s\n", res_str);
char	*add_path(t_cmd_args *args)
{
	char		*res_str;
	const char	*cmd = args->cmdpath[0];

	if (cmd == NULL)
		return (NULL);
	if (cmd_type_is(cmd) == COM)
		res_str = search_cmd_path(cmd);
	else
		res_str = ft_strdup(cmd);
	return (res_str);
}
