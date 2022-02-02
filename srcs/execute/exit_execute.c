/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_execute.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 16:12:53 by sosugimo          #+#    #+#             */
/*   Updated: 2022/02/01 22:09:13 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execute.h"
#include <errno.h>

static bool	is_numeric_string(char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (false);
		str++;
	}
	return (true);
}

static int	cmdpath_len(char **cmdpath)
{
	int	i;

	i = 0;
	while (cmdpath[i] != NULL)
		i++;
	return (i);
}

static void	numeric_argument_error(char *str)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	exit(255);
}

void	execute_exit(t_cmd_args *args)
{
	int	exit_status;

	errno = 0;
	if (cmdpath_len(args->cmdpath) > 2)
	{
		ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
		return ;
	}
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (args->cmdpath[1] == NULL)
		exit(g_minishell.exit_status);
	if (!is_numeric_string(args->cmdpath[1]))
		numeric_argument_error(args->cmdpath[1]);
	exit_status = ft_atoi(args->cmdpath[1]);
	if (errno == EINVAL)
		numeric_argument_error(args->cmdpath[1]);
	exit(exit_status);
}
