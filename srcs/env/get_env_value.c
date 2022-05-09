/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymori <ymori@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 14:37:41 by ymori             #+#    #+#             */
/*   Updated: 2022/04/30 14:37:44 by ymori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


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
