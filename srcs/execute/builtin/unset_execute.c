/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_execute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 16:12:26 by sosugimo          #+#    #+#             */
/*   Updated: 2022/02/05 13:43:16 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "msh_error.h"

void	execute_unset(t_cmd_args *args)
{
	size_t	i;
	int		status;

	i = 1;
	status = EXIT_SUCCESS;
	while (args->cmdpath[i])
	{
		if (satisfy_env_name_rule(args->cmdpath[i]) == true)
			envlist_del(&g_minishell.env, args->cmdpath[i]);
		else
		{
			msh_fatal("unset");
			status = EXIT_FAILURE;
		}
		i++;
	}
	g_minishell.exit_status = status;
	return ;
}
