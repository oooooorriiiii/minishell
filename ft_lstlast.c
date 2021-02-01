/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymori <ymori@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 18:46:32 by ymori             #+#    #+#             */
/*   Updated: 2021/02/02 01:55:35 by ymori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*lst_tmp;

	lst_tmp = lst;
	if (lst == NULL)
		return (NULL);
	while (lst_tmp->next != NULL)
		lst_tmp = lst_tmp->next;
	return (lst_tmp);
}
