/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymori <ymori@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 22:37:13 by ymori             #+#    #+#             */
/*   Updated: 2021/02/02 01:54:47 by ymori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*lst_tmp;
	t_list	*tmp;

	lst_tmp = *lst;
	while (lst_tmp != NULL)
	{
		tmp = lst_tmp->next;
		ft_lstdelone(lst_tmp, del);
		lst_tmp = tmp;
	}
	*lst = NULL;
}
