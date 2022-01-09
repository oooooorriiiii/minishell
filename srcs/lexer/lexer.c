/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymori <ymori@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 22:23:51 by ymori             #+#    #+#             */
/*   Updated: 2022/01/10 03:03:59 by ymori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdio.h>

static bool	exist_closing_token(char *line, char token)
{
	char	*current_char;

	current_char = line;
	current_char++;
	while (*current_char)
	{
		if (*current_char == token)
		{
			line = current_char;
			return (true);
		}
		current_char++;
	}
	return (false);
}

bool	between_quotes(char *line)
{
	char	*current_char;

	current_char = line;
	if (is_quote(*current_char) && exist_closing_token(line, *current_char))
		return (true);
	return (false);
}

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

/*
** 
*/
void	lexer(char *original_line, t_token **lex_list)
{
	t_list	*init_line_list;

	init_line_list = token_split_to_list(original_line);
	list_print(init_line_list);
}
