/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymori <ymori@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 18:43:47 by ymori             #+#    #+#             */
/*   Updated: 2022/01/19 15:06:59 by ymori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	list_print(t_list *list)
{
	if (list == NULL)
	{
		printf("NULL\n");
		return ;
	}
	while (list->next)
	{
		printf("value: %s\n", (char *)(list->content));
		list = list->next;
	}
	printf("value: %s\n", (char *)(list->content));
}

void	print_token_list(t_token_list *list)
{
	printf("********RET LIST********\n");
	if (list == NULL)
	{
		printf("NULL\n");
		return ;
	}
	while (list->next)
	{
		printf("value: %s\n", list->val);
		printf("type: %d\n", list->type);
		list = list->next;
	}
	printf("value: %s\n", list->val);
	printf("type: %d\n", list->type);
}
