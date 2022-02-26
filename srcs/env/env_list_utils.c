/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymori <ymori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 03:38:57 by ymori             #+#    #+#             */
/*   Updated: 2022/01/30 03:39:01 by ymori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	t_envlist	*lst_last;

	lst_last = envlist;
	if (envlist == NULL)
		return (NULL);
	while (lst_last->next)
		lst_last = lst_last->next;
	return (lst_last);
}

/*
 * **p_envlist:  pointer of envlist
 * *new_envlist: pointer of envlist element
 */
void	envlist_add_back(t_envlist **p_envlist, t_envlist *new_elem)
{
	t_envlist	*lst_last;

	if (new_elem == NULL || p_envlist == NULL)
		return ;
	if (*p_envlist == NULL)
	{
		envlist_listlast(*p_envlist)->next = new_elem;
		new_elem->next = NULL;
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
