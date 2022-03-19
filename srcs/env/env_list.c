/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 03:39:06 by ymori             #+#    #+#             */
/*   Updated: 2022/02/06 00:24:50 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_env.h"
#include "msh_error.h"

#include <stdio.h>

void	print_envlist(t_envlist *list)
{
	printf("------env list------\n");
	if (list == NULL)
	{
		printf("NULL\n");
		return ;
	}
	while (list->next)
	{
		printf("key     : %s\n", list->key);
		printf("value   : %s\n", list->value);
		printf("is_shell: %d\n", list->is_shell_var);
		list = list->next;
	}
	printf("key     : %s\n", list->key);
	printf("value   : %s\n", list->value);
	printf("is_shell: %d\n", list->is_shell_var);
}

/*
 * used by envlist_listnew
 */
static void	set_elements(char *env, t_envlist *new)
{
	char	*key;
	char	*value;
	char	*equal_and_beyond;
	size_t	key_len;

	equal_and_beyond = ft_strchr(env, '=');
	key_len = equal_and_beyond - env;
	key = ft_substr(env, 0, key_len);
	value = ft_substr(env, key_len + 1, ft_strlen(env) - key_len - 1);
	new->key = key;
	new->value = value;
	new->is_shell_var = true;
}

/*
 * create new element of envlist.
 */
t_envlist	*envlist_listnew(t_envlist *current, char *env)
{
	t_envlist	*new_env;

	new_env = malloc(sizeof(t_envlist));
	set_elements(env, new_env);
	current->next = new_env;
	return (new_env);
}

/*
 * Create first environ list.
 * Used only for initialization.
 */
t_envlist	*create_envlist(char **envp)
{
	t_envlist	head;
	t_envlist	*current;
	size_t		i;

	i = 0;
	current = &head;
	if (envp[i] == NULL)
		return (NULL);
	while (envp[i])
	{
		current = envlist_listnew(current, envp[i]);
		i++;
	}
	current->next = NULL;
	return (head.next);
}
