/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymori <ymori@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 23:39:03 by ymori             #+#    #+#             */
/*   Updated: 2021/02/02 01:57:06 by ymori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*lst_tmp;

	lst_tmp = lst;
	if (lst == NULL || f == NULL)
		return ;
	while (lst_tmp != NULL)
	{
		f(lst_tmp->content);
		lst_tmp = lst_tmp->next;
	}
}
