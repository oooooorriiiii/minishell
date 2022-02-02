//
// Created by ymori on 2/2/22.
//

#include "minishell.h"
#include "msh_env.h"

char	*get_env_value(const char *key)
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
