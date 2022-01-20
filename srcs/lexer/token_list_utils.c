/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymori <ymori@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 11:53:19 by ymori             #+#    #+#             */
/*   Updated: 2022/01/20 14:09:02 by ymori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static t_token_list	*token_list_last(t_token_list *lst)
{
	t_token_list	*lst_tmp;

	lst_tmp = lst;
	if (lst == NULL)
		return (NULL);
	while (lst_tmp->next)
		lst_tmp = lst_tmp->next;
	return (lst_tmp);
}

t_token_list	*token_listnew(char *token, t_token_type token_type)
{
	t_token_list	*new_elem;

	new_elem = malloc(sizeof(t_token_list));
	if (new_elem == NULL)
		return (NULL);
	new_elem->val = ft_strdup(token);
	new_elem->type = token_type;
	new_elem->next = NULL;
	return (new_elem);
}

void	token_list_add_back(t_token_list **lst, t_token_list *new_elem)
{
	t_token_list	*lst_last;

	if (lst == NULL || new_elem == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new_elem;
		new_elem->next = NULL;
		return ;
	}
	lst_last = token_list_last(*lst);
	lst_last->next = new_elem;
	new_elem->next = NULL;
}
