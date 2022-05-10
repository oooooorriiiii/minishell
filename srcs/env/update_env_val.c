/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env_val.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 03:39:43 by ymori             #+#    #+#             */
/*   Updated: 2022/02/06 00:24:43 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "msh_env.h"
#include "msh_error.h"
#include "minishell.h"
#include <stdlib.h>

static void	set_env_value(t_envlist *envlist, const char *new_value, \
							bool append_flag)
{
	char	*old_value;

	old_value = envlist->value;
	if (append_flag == true)
	{
		if (old_value || new_value)
			envlist->value = ft_strjoin(old_value, new_value);
		else
			envlist->value = NULL;
	}
	else
	{
		if (new_value)
			envlist->value = ft_strdup(new_value);
		else
			envlist->value = NULL;
	}
	free_str(&old_value);
}

t_envlist	*recreate_envlist(char *env_str)
{
	t_envlist	*envlist;
	char		*sep;

	envlist = malloc(sizeof(t_envlist));
	if (envlist == NULL)
		exit(-1); // TODO: EXIT STATUS
	sep = ft_strchr(env_str, '=');
	if (!sep)
	{
		envlist->key = ft_strdup(env_str);
		if (envlist->key == NULL)
			exit(-1); // TODO: EXIT STATUS
		envlist->value = NULL;
	}
	else
	{
		envlist->key = ft_substr(env_str, 0, sep - env_str);
		envlist->value = ft_strdup(sep + 1);
		if (envlist->key == NULL || envlist->value == NULL)
			exit(-1); // TODO: EXIT STATUS
	}
	envlist->is_shell_var = true;
	envlist->next = NULL;
	return (envlist);
}

/*
 * if used by store_env(), is_env_var is true.
 */
void	update_env_val(const char *env_key, const char *new_env_val, \
						bool is_env_var, bool append_flag)
{
	t_envlist	*envlist;

	if (!env_key)
		return ;
	envlist = msh_get_envlist(env_key);
	if (envlist == NULL)
	{
		envlist = recreate_envlist((char *)env_key);
		envlist->is_shell_var = is_env_var;
		envlist_add_back(&(g_minishell.env), envlist);
	}
	else
	{
		if (envlist->is_shell_var == false)
			envlist->is_shell_var = is_env_var;
	}
	set_env_value(envlist, new_env_val, append_flag);
}
