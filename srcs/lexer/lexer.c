/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymori <ymori@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 22:23:51 by ymori             #+#    #+#             */
/*   Updated: 2022/01/14 17:48:20 by ymori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdio.h>

int	ft_isblank(int c)
{
	if (c == ' ' || c == '\t')
	{
		return (1);
	}
	return (0);
}

t_token	*token_new(char *element, t_token_type token_type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	token->val = ft_strdup(element);
	token->type = token_type;
	return (token);
}

void	quote_process(t_list **token_list, char **token, t_list **ret_list)
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
		ft_lstadd_back(ret_list, ft_lstnew(token_new(*token, TOKEN))); // TODO: TOKEN type
		free_set((void **)token, ft_strdup(""));
	}
	return ;
}

void	literal_process(t_list **token_list, char **token, t_list **ret_list)
{
	free_set((void **)token, \
				ft_strjoin(*token, (char *)(*token_list)->content));
	*token_list = (*token_list)->next;
	if (*token_list == NULL || (*token_list != NULL && \
		ft_strchr("\t\n\v\f\r <>|", *(char *)(*token_list)->content) != NULL))
	{
		ft_lstadd_back(ret_list, ft_lstnew(token_new(*token, TOKEN_LITERAL)));
		free_set((void **)token, ft_strdup(""));
	}
}

// void pointer??
// because using ft_strdup in token_new
void	token_list_free(void *element)
{
	t_token	*token;

	token = (t_token *)element;
	free(token->val);
	token->val = NULL;
	free(token);
}

t_lexer	*lexer_new(t_list *token_list)
{
	t_lexer	*lexer;

	lexer = malloc(sizeof(t_lexer));
	lexer->len = ft_lstsize(token_list);
	lexer->list = token_list;
	return (lexer);
}

static bool	is_operator(char *element)
{
	if (!ft_strncmp(element, "|", 1) || !ft_strncmp(element, ">>", 2) || \
			!ft_strncmp(element, "<<", 2) || !ft_strncmp(element, ">", 1) || \
			!ft_strncmp(element, "<", 1))
		return (true);
	return (false);
}

void	operetor_analysis(t_list **token_list, char *token, \
							t_list *ret_list, char *element)
{
	if (*element == '\'' || *element == '\"')
		quote_process(token_list, &token, &ret_list);
	else if (ft_strncmp(element, "<<", 2) == 0)
	{
		//TODO: Heredoc
	}
	else if (ft_strncmp(element, ">>", 2) == 0)
	{
		ft_lstadd_back(&ret_list, \
						ft_lstnew(token_new(element, TOKEN_REDIRECT))); // TODO: REDIRECT type
		*token_list = (*token_list)->next;
	}
	else if (*element == '<' || *element == '>' || *element == '|')
	{
		ft_lstadd_back(&ret_list, ft_lstnew(token_new(element, *element))); // TODO: TOKEN -> <, >, PIPE
		*token_list = (*token_list)->next;
	}
	return ;
}

void	lexcal_analysis(t_list *token_list, t_lexer **lex_list)
{
	t_list	*ret_list;
	char	*element;
	char	*token;

	ret_list = NULL;
	token = ft_strdup("");
	while (token_list)
	{
		element = (char *)token_list->content;
		if (ft_isblank(*element))
			token_list = token_list->next;
		else if (is_operator(element))
			operetor_analysis(&token_list, token, ret_list, element);
		else
			literal_process(&token_list, &token, &ret_list);
	}
	free(token);
	list_print_token(ret_list); // DEBUG
	*lex_list = lexer_new(ret_list);
}

/*
** 
*/
void	lexer(char *original_line, t_lexer **lex_list)
{
	t_list	*init_line_list;

	init_line_list = token_split_to_list(original_line);
	list_print(init_line_list);
	puts("*****");
	lexcal_analysis(init_line_list, lex_list);
	ft_lstclear(&init_line_list, free);
}
