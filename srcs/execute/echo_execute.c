/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_execute.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 16:09:29 by sosugimo          #+#    #+#             */
/*   Updated: 2022/01/30 10:48:30 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execute.h"

bool	check_option(char **cmdarg, int argc)
{
	char	*option;

	if (argc < 1)
		return (false);
	option = cmdarg[1];
	if (option[0] == '-' && option[1] == 'n')
		return (true);
	return (false);
}

void	execute_echo(t_cmd_args *args)
{
	int	i;
	int	fd;

	i = 1;
	while (i < args->cmdpath_argc)
	{
		if (!(i == 1
				&& args->cmdpath[i][0] == '-' && args->cmdpath[i][1] == 'n'))
			printf("%s", args->cmdpath[i]);
		i++;
	}
	if (!check_option(args->cmdpath, args->cmdpath_argc))
		printf("\n");
}
