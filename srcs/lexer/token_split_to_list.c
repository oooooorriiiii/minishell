/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_split_to_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymori <ymori@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 14:27:33 by ymori             #+#    #+#             */
/*   Updated: 2022/01/27 03:15:48 by ymori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "msh_error.h"
#include "utils.h"

/*
 * This function need free
 */
char	*char_to_str(char c)
{
	char	*ret_str;

	ret_str = malloc(2 * sizeof(char));
	ret_str[0] = c;
	ret_str[1] = '\0';
	return (ret_str);
}

void	free_set(void **dst, void *src)
{
	free(*dst);
	*dst = src;
}

t_list	*token_split_to_list(char *line)
{
	t_list	*new_list;
	char	*head;

	new_list = NULL;
	while (*line != '\0')
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
	merge_redirections(new_list);
	return (new_list);
}
