/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymori <ymori@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 18:43:47 by ymori             #+#    #+#             */
/*   Updated: 2022/01/11 18:46:07 by ymori            ###   ########.fr       */
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

void	list_print_token(t_list *list)
{
	puts("ret list");
	if (list == NULL)
	{
		printf("NULL\n");
		return ;
	}
	while (list->next)
	{
		printf("value: %s\n", (char *)(((t_token *)(list->content))->val));
		printf("type: %d\n", (int)(((t_token *)(list->content))->type));
		list = list->next;
	}
	printf("value: %s\n", (char *)(((t_token *)(list->content))->val));
	printf("type: %d\n", (int)(((t_token *)(list->content))->type));
}
