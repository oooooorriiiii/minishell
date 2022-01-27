/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_execute.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 16:09:29 by sosugimo          #+#    #+#             */
/*   Updated: 2022/01/27 12:32:50 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execute.h"

void	execute_echo(t_cmd_args *args)
{
	printf(" execute_echo \n");
}

t_bool	is_option_str(char *str)
{
	size_t	len;

	if (!str)
		return (FALSE);
	len = ft_strlen(str);
	if (len < 2 || str[0] != '-' || str[1] != 'n')
		return (FALSE);
	str++;
	while (*str == 'n')
		str++;
	if (*str == '\0')
		return (TRUE);
	return (FALSE);
}

void	skip_option(char **args, t_bool *flag, size_t *index)
{
	while (args[*index])
	{
		if (is_option_str(args[*index]))
			*flag = TRUE;
		else
			break ;
		*index += 1;
	}
}

int	execute_echo(char **args)
{
	size_t	index;
	t_bool	option_flag;

	index = 1;
	option_flag = FALSE;
	skip_option(args, &option_flag, &index);
	while (args[index])
	{
		ft_putstr_fd(args[index], STDOUT_FILENO);
		if (args[index + 1] != NULL)
			ft_putstr_fd(" ", STDOUT_FILENO);
		index++;
	}
	if (option_flag == FALSE)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
