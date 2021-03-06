/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_env_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymori <ymori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 03:39:26 by ymori             #+#    #+#             */
/*   Updated: 2022/01/30 03:39:32 by ymori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_env.h"
#include "msh_error.h"

static bool	is_countable(t_envlist *envlist)
{
	if (envlist->value == NULL)
		return (false);
	if (envlist->is_shell_var == false)
		return (false);
	return (true);
}

size_t	get_envlist_size(t_envlist *envlist)
{
	size_t	size;

	size = 0;
	while (envlist)
	{
		if (is_countable(envlist))
			size++;
		envlist = envlist->next;
	}
	return (size);
}

char	**gen_env_str(t_envlist *envlist)
{
	char			**ret_strs;
	char			*tmp;
	size_t			i;
	const size_t	envlist_size = get_envlist_size(envlist);

	ret_strs = malloc(sizeof(char *) * (envlist_size + 1));
	if (ret_strs == NULL)
		msh_fatal("env error");
	i = 0;
	while (i < envlist_size)
	{
		if (is_countable(envlist))
		{
			ret_strs[i] = ft_strjoin(envlist->key, "=");
			tmp = ret_strs[i];
			ret_strs[i] = ft_strjoin(ret_strs[i], envlist->value);
			free(tmp);
			i++;
		}
		envlist = envlist->next;
	}
	ret_strs[i] = NULL;
	return (ret_strs);
}
