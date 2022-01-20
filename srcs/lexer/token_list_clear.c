/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_clear.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymori <ymori@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 14:00:45 by ymori             #+#    #+#             */
/*   Updated: 2022/01/20 14:01:12 by ymori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	token_list_delone(t_token_list *lst)
{
	if (lst == NULL)
		return ;
	free(lst->val);
	free(lst);
}

void	token_list_clear(t_token_list **lst)
{
	t_token_list	*lst_tmp;
	t_token_list	*tmp;

	lst_tmp = *lst;
	while (lst_tmp)
	{
		tmp = lst_tmp->next;
		token_list_delone(lst_tmp);
		lst_tmp = tmp;
	}
	*lst = NULL;
}
