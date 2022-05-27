/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 16:12:40 by sosugimo          #+#    #+#             */
/*   Updated: 2022/01/24 13:38:56 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static void	print_env(t_envlist *envlist)
{
	if (envlist->value == NULL)
		return ;
	if (envlist->is_shell_var == false)
		return ;
	printf("%s=%s\n", envlist->key, envlist->value);
}

// TODO: return status ??
//	printf(" execute_env \n"); // DEBUG
//	print_envlist(envlist);
void	execute_env(t_cmd_args *args)
{
	t_envlist	*envlist;

	(void)args;
	envlist = g_minishell.env;
	while (envlist)
	{
		print_env(envlist);
		envlist = envlist->next;
	}
	return ;
}
