/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 14:49:22 by sosugimo          #+#    #+#             */
/*   Updated: 2022/02/03 14:51:25 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parser.h"
#include "../includes/execute.h"
#include "../includes/lexer.h"

int	isenval(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

void	reset_status(int *status)
{
	if (*status == SINGLE_Q * 2 || *status == DOUBLE_Q * 2)
		*status = 0;
}

void	double_free(char **buf1, char **buf2)
{
	free(*buf1);
	free(*buf2);
}

void	double_reset(int *status, int *status2)
{
	reset_status(status);
	reset_status(status2);
}

void	int_init(int *status, int *status2, int *len)
{
	*status = 0;
	*status2 = 0;
	*len = 0;
}
