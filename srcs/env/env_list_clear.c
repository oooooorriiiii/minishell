/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_clear.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymori <ymori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 03:38:45 by ymori             #+#    #+#             */
/*   Updated: 2022/01/30 03:38:50 by ymori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_env.h"

void	envlist_delone(t_envlist *list)
{
	if (list == NULL)
		return ;
	free(list->key);
	free(list->value);
	free(list);
}

void	envlist_clear(t_envlist **list)
{
	t_envlist	*list_tmp;
	t_envlist	*next_tmp;

	list_tmp = *list;
	while (list_tmp)
	{
		next_tmp = list_tmp->next;
		envlist_delone(list_tmp);
		list_tmp = next_tmp;
	}
	*list = NULL;
}
