/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_execute.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 16:09:29 by sosugimo          #+#    #+#             */
/*   Updated: 2022/05/15 11:41:31 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

bool	check_option(char **cmdarg, int argc)
{
	char	*option;

	if (argc <= 1)
		return (false);
	option = cmdarg[1];
	if (option[0] == '-' && option[1] == 'n')
		return (true);
	return (false);
}

/**
 *
 * @param args
 * cmdpath[0]: command name
 * cmdpath[1..]: arguments
 */
void	execute_echo(t_cmd_args *args)
{
	int		i;
	bool	no_new_line;

	g_minishell.exit_status = 0;
	no_new_line = false;
	i = 1;
	if (args->cmdpath[1] == NULL)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		return ;
	}
	while (!ft_strcmp(args->cmdpath[i], "-n"))
	{
		no_new_line = true;
		if (args->cmdpath[++i] == NULL)
			return ;
	}
	ft_putstr_fd(args->cmdpath[i++], STDOUT_FILENO);
	while (args->cmdpath[i])
	{
		ft_putstr_fd(" ", STDOUT_FILENO);
		ft_putstr_fd(args->cmdpath[i++], STDOUT_FILENO);
	}
	if (no_new_line == false)
		ft_putstr_fd("\n", STDOUT_FILENO);
}
