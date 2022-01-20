/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymori <ymori@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 22:23:51 by ymori             #+#    #+#             */
/*   Updated: 2022/01/20 23:56:40 by ymori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdio.h>

void	quote_process(t_list **token_list, char **token, \
						t_token_list **ret_list)
{
	const char	quote = *(char *)(*token_list)->content;

	free_set((void **)token, \
				ft_strjoin(*token, (char *)(*token_list)->content));
	while (true)
	{
		*token_list = (*token_list)->next;
		if (*token_list == NULL)
			printf("Close the quote\n"); // TODO: exit
		free_set((void **)token, \
					ft_strjoin(*token, (char *)(*token_list)->content));
		if (*(char *)(*token_list)->content == quote)
		{
			*token_list = (*token_list)->next;
			break ;
		}
	}
	if (*token_list == NULL || (*token_list != NULL && \
		ft_strchr("\t\n\v\f\r <>|", *(char *)(*token_list)->content) != NULL))
	{
		// TODO: hoge
		token_list_add_back(ret_list, token_listnew(*token, TOKEN)); // TODO: TOKEN type
		free_set((void **)token, ft_strdup(""));
	}
	return ;
}

void
	literal_process(t_list **token_list, char **token, t_token_list **ret_list)
{
	free_set((void **)token, \
				ft_strjoin(*token, (char *)(*token_list)->content));
	*token_list = (*token_list)->next;
	if (*token_list == NULL || (*token_list != NULL && \
		ft_strchr("\t\n\v\f\r <>|", *(char *)(*token_list)->content) != NULL))
	{
		token_list_add_back(ret_list, token_listnew(*token, CHAR_GENERAL));
		free_set((void **)token, ft_strdup(""));
	}
}

void	operetor_analysis(t_list **token_list, char *token, \
							t_token_list *ret_list, char *element)
{
	if (*element == '\'' || *element == '\"')
		quote_process(token_list, &token, &ret_list);
	else if (ft_strncmp(element, "<<", 2) == 0)
	{
		//TODO: Heredoc
	}
	else if (ft_strncmp(element, ">>", 2) == 0)
	{
		token_list_add_back(&ret_list, \
							token_listnew(element, CHAR_DBLGREATER));
		*token_list = (*token_list)->next;
	}
	else if (*element == '<' || *element == '>' || *element == '|')
	{
		token_list_add_back(&ret_list, \
							token_listnew(element, *element));
		*token_list = (*token_list)->next;
	}
	return ;
}

void	lexcal_analysis(t_list *init_token_list, t_lexer **lex_list)
{
	t_token_list	*ret_list;
	char			*element;
	char			*token;

	ret_list = NULL;
	token = ft_strdup("");
	while (init_token_list)
	{
		element = (char *)init_token_list->content;
		if (ft_isblank(*element))
			init_token_list = init_token_list->next;
		else if (is_operator(element))
			operetor_analysis(&init_token_list, token, ret_list, element);
		else
			literal_process(&init_token_list, &token, &ret_list);
	}
	free(token);
	print_token_list(ret_list);// DEBUG
	*lex_list = lexer_new(ret_list);
}

/*
**
*/
void	lexer(char *original_line, t_lexer **lex_list)
{
	t_list	*init_token_list;

	init_token_list = token_split_to_list(original_line);
	list_print(init_token_list);
	puts("*****");
	lexcal_analysis(init_token_list, lex_list);
	ft_lstclear(&init_token_list, free);
}
