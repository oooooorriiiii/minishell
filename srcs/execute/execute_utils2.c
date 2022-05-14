/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 10:23:48 by sosugimo          #+#    #+#             */
/*   Updated: 2022/05/14 10:46:34 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execute.h"

char	**functional_malloc(int i)
{
	char	**res;

	res = (char **)malloc(sizeof(char *) * (i + 1));
	malloc_error_exec(NULL, res, NULL);
	return (res);
}

int	get_list_len(t_astree *argNode)
{
	int	i;

	i = 0;
	while (argNode != NULL && (argNode->type == NODE_ARGUMENT
			|| argNode->type == NODE_CMDPATH))
	{
		argNode = argNode->right;
		i++;
	}
	return (i);
}

bool	check_componet(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '\"')
			return (false);
		i++;
	}
	return (true);
}
