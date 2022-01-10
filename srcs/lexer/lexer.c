/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymori <ymori@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 22:23:51 by ymori             #+#    #+#             */
/*   Updated: 2022/01/11 01:31:57 by ymori            ###   ########.fr       */
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

	printf("quote: %c\n", quote);
	free_set((void **)token, \
				ft_strjoin(*token, (char *)(*token_list)->content));
	while (true)
	{
		*token_list = (*token_list)->next;
		if (*token_list == NULL)
			printf("Close the quote\n"); // TODO: exit
		free_set((void **)token, ft_strjoin(*token, (char *)(*token_list)->content));
		if (*(char *)(*token_list)->content == quote)
		{
			*token_list = (*token_list)->next;
			break ;
		}
	}
	if (*token_list == NULL || (*token_list != NULL && ft_strchr("\t\n\v\f\r <>|", *(char *)(*token_list)->content) != NULL))
	{
		// TODO: hoge
		ft_lstadd_back(ret_list, ft_lstnew(token_new(*token, TOKEN))); // TODO: TOKEN type
		free_set((void **)token, ft_strdup(""));
	}
	return ;
}

void	general_token_process(t_list **token_list, char **token, t_list **ret_list)
{
	free_set((void **)token, ft_strjoin(*token, (char *)(*token_list)->content));
	*token_list = (*token_list)->next;
	if (*token_list == NULL || (*token_list != NULL && ft_strchr("\t\n\v\f\r <>|", *(char *)(*token_list)->content) != NULL))
	{
		ft_lstadd_back(ret_list, ft_lstnew(token_new(*token, TOKEN)));
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

//
// typedef struct	s_token
// {
// 	t_token_type	type;
// 	char			*val;
// 	// struct s_token	*next;
// }				t_token;
//
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
		// TODO: separate function, is_operator, other
		printf("element: %s\n", element); // DEBUG
		printf("*element: %c\n", *element); // DEBUG
		if (ft_isblank(*element))
			token_list = token_list->next;
		else if (*element == '\'' || *element == '\"')
		{
			quote_process(&token_list, &token, &ret_list);
		}
		else if (ft_strncmp(element, "<<", ft_strlen(element)) == 0)
		{
			//TODO: Heredoc
		}
		else if (ft_strncmp(element, ">>", ft_strlen(element)) == 0)
		{
			ft_lstadd_back(&ret_list, ft_lstnew(token_new(element, REDIRECT))); // TODO: REDIRECT type
			token_list = token_list->next;
		}
		else if (*element == '<' || *element == '>' || *element == '|')
		{
			ft_lstadd_back(&ret_list, ft_lstnew(token_new(element, TOKEN))); // TODO: TOKEN -> <, >, PIPE
			token_list = token_list->next;
		}
		else
			general_token_process(&token_list, &token, &ret_list);
	}
	free(token);
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
