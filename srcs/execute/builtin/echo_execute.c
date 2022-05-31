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

//void	execute_echo(t_cmd_args *args)
//{
//	int	i;
//	int	flag;
//
//	i = 1;
//	flag = 0;
//	printf("%s\n", args->cmdpath[i]); // D
//	printf("%d\n", args->cmdpath_argc); // D
//	while (i < args->cmdpath_argc)
//	{
//		while (flag == 0 && check_option(args->cmdpath, args->cmdpath_argc)
//			&& !ft_strcmp(args->cmdpath[i], "-n"))
//			i++;
//		flag = 1;
//		printf("%s", args->cmdpath[i]);
//		if (i < args->cmdpath_argc - 1 && !(i == 1
//				&& check_option(args->cmdpath, args->cmdpath_argc)))
//			printf(" ");
//		i++;
//	}
//	if (!check_option(args->cmdpath, args->cmdpath_argc))
//		printf("\n");
//	g_minishell.exit_status = 0;
//};
//

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

	no_new_line = false;
	i = 1;
	if (args->cmdpath[1] == NULL)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		g_minishell.exit_status = 0;
		return ;
	}
	while (!ft_strcmp(args->cmdpath[i], "-n"))
	{
		no_new_line = true;
		if (args->cmdpath[++i] == NULL)
		{
			g_minishell.exit_status = 0;
			return;
		}
	}
	ft_putstr_fd(args->cmdpath[i++], STDOUT_FILENO);
	while (args->cmdpath[i])
	{
		ft_putstr_fd(" ", STDOUT_FILENO);
		ft_putstr_fd(args->cmdpath[i++], STDOUT_FILENO);
	}
	if (no_new_line == false)
		ft_putstr_fd("\n", STDOUT_FILENO);
	g_minishell.exit_status = 0;
}