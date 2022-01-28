//
// Created by ymori on 1/28/22.
//

#include "msh_env.h"
#include "msh_error.h"

static bool	satisfy_conditions(t_envlist *envlist)
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
		if (satisfy_conditions(envlist))
			size++;
		envlist = envlist->next;
	}
	return (size);
}

char	**gen_env_str(t_envlist *envlist)
{
	char 	**ret_strs;
	char 	*tmp;
	size_t	i;
	const size_t	envlist_size = get_envlist_size(envlist);

	ret_strs = malloc(sizeof(char *) * (envlist_size + 1));
	if (ret_strs == NULL)
		msh_fatal("env error");
	i = 0;
	while (i < envlist_size)
	{
		if (satisfy_conditions(envlist))
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
