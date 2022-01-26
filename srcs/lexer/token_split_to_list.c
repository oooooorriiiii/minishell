/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_split_to_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymori <ymori@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 14:27:33 by ymori             #+#    #+#             */
/*   Updated: 2022/01/26 16:59:18 by ymori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	free_set(void **dst, void *src)
{
	free(*dst);
	*dst = src;
}

void	merge_doutle_tokens(t_list **tokens, char c)
{
	char		new_token_elem[3];
	t_list		*next;

	if (*(char *)(*tokens)->content == c && \
			*(char *)(*tokens)->next->content == c)
	{
		next = (*tokens)->next->next;
		new_token_elem[0] = c;
		new_token_elem[1] = c;
		new_token_elem[2] = '\0';
		free_set((void **)&(*tokens)->content, ft_strdup(new_token_elem));
		free((*tokens)->next->content);
		free((*tokens)->next);
		(*tokens)->next = next;
	}
}

void	merge_redirections(t_list *tokens)
{
	if (tokens == NULL)
		ft_fatal("token error");
	while (tokens && tokens->next)
	{
		merge_doutle_tokens(&tokens, '>');
		merge_doutle_tokens(&tokens, '<');
		tokens = tokens->next;
	}
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
