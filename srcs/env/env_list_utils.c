//
// Created by ymori on 1/29/22.
//

#include "msh_env.h"
#include "utils.h"
#include "minishell.h"

t_envlist	*msh_get_envlist(const char *key)
{
	t_envlist	*current;

	if (!g_minishell.env || !key)
		return (NULL);
	current = g_minishell.env;
	while (current)
	{
		if (ft_strcmp(current->key, (char *)key) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}

t_envlist	*envlist_listlast(t_envlist *envlist)
{
	t_envlist	*list_last;

	if (!envlist)
		return (NULL);
	list_last = envlist;
	while (list_last->next)
		list_last = list_last->next;
	return (list_last);
}

void	envlist_add_back(t_envlist **p_envlist, t_envlist *new_envlist)
{
	if (!new_envlist || !p_envlist)
		return ;
	if (!*p_envlist)
		*p_envlist = new_envlist;
	else
	{
		envlist_listlast(*p_envlist)->next = new_envlist;
		new_envlist->next = NULL;
	}
}

void	envlist_del(t_envlist **p_envlist, char *key)
{
	t_envlist	*current;
	t_envlist	*prev;

	prev = NULL;
	current = *p_envlist;
	while (current)
	{
		if (!ft_strncmp(current->key, key, ft_strlen(key) + 1))
		{
			if (prev)
				prev->next = current->next;
			else
				*p_envlist = current->next;
			free_str(&(current->key));
			free_str(&(current->value));
			free(current);
			current = NULL;
			break ;
		}
		prev = current;
		current = current->next;
	}
}
