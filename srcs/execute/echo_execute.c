/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_execute.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 16:09:29 by sosugimo          #+#    #+#             */
/*   Updated: 2022/02/09 15:05:14 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execute.h"

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

void	execute_echo(t_cmd_args *args)
{
	int	i;
//	int	j; // COMMENT OUT: ymori
//	int	fd; // COMMENT OUT: ymori
	int	flag;

	i = 1;
//	j = 0; // COMMENT OUT: ymori
	flag = 0;
	while (i < args->cmdpath_argc)
	{
//		j = 0; // COMMENT OUT: ymori
		while (flag == 0 && check_option(args->cmdpath, args->cmdpath_argc)
			&& !strcmp(args->cmdpath[i], "-n"))
			i++;
		flag = 1;
		printf("%s", args->cmdpath[i]);
		if (i < args->cmdpath_argc - 1 && !(i == 1
				&& check_option(args->cmdpath, args->cmdpath_argc)))
			printf(" ");
		i++;
	}
	if (!check_option(args->cmdpath, args->cmdpath_argc))
		printf("\n");
	g_minishell.exit_status = 0;
}
