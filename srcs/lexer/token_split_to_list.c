/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_split_to_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymori <ymori@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 14:27:33 by ymori             #+#    #+#             */
/*   Updated: 2022/01/10 14:28:07 by ymori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_list	*token_split_to_list(char *line)
{
	t_list	*new_list;
	char	*head;

	new_list = NULL;
	while (*line)
	{
		if (ft_strchr("\'\"\t\n\v\f\r <>|", *line) != NULL)
		{
			ft_lstadd_back(&new_list, ft_lstnew(ft_substr(line, 0, 1)));
			line++;
		}
		else
		{
			head = line;
			while (ft_strchr("\'\"\t\n\v\f\r <>|", *line) == NULL)
				line++;
			ft_lstadd_back(&new_list, \
				ft_lstnew(ft_substr(head, 0, line - head)));
		}
	}
	return (new_list);
}
