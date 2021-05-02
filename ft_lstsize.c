/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymori <ymori@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 17:24:14 by ymori             #+#    #+#             */
/*   Updated: 2021/05/02 13:39:35 by ymori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		size;
	t_list	*lst_tmp;

	size = 0;
	lst_tmp = lst;
	while (lst_tmp != NULL)
	{
		lst_tmp = lst_tmp->next;
		size++;
	}
	return (size);
}
