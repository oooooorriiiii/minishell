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

void	free_set(void **dst, void *src)
{
	free(*dst);
	*dst = src;
}

void	merge_double_tokens(t_list **tokens, char c)
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
		msh_fatal("token error");
	while (tokens && tokens->next)
	{
		merge_double_tokens(&tokens, '>');
		merge_double_tokens(&tokens, '<');
		tokens = tokens->next;
	}
}

static char	*expand_env(char *content)
{
	char	*tmp;

	if (!ft_strcmp(content, "?"))
	{
		if (g_minishell.heredoc_status != 0)
			tmp = ft_itoa(g_minishell.heredoc_status);
		else
			tmp = ft_itoa(g_minishell.exit_status);
		g_minishell.heredoc_status = 0;
	}
	else
	{
		tmp = get_env_value(content);
		if (tmp == NULL)
			tmp = "";
		tmp = ft_strdup(tmp);
	}
	return (tmp);
}

//printf("tmp: %s\n", tmp);
void	merge_doutle_string(t_list **tokens)
{
	char	*tmp;
	t_list	*next;

	next = (*tokens)->next->next;
	tmp = ft_strjoin((*tokens)->content, (*tokens)->next->content);
	free_set((void **)&(*tokens)->content, tmp);
	free((*tokens)->next->content);
	free((*tokens)->next);
	(*tokens)->next = next;
}

/*
 * Need free
 */
char	*char_to_str(char c)
{
	char	*ret_str;

	ret_str = malloc(2 * sizeof(char));
	ret_str[0] = c;
	ret_str[1] = '\0';
	return (ret_str);
}

bool	exist_double_token(char *str, char token)
{
	char	*tmp;
	char	*head;
	char	*cmp_str;
	bool	ret;

	ret = false;
	cmp_str = char_to_str(token);
	if (ft_strchr(str, token) == NULL)
	{
		free_str(&cmp_str);
		return (false);
	}
	else
	{
		head = str;
		while (ft_strchr(str, token))
			str++;
		tmp = ft_substr(head, 0, str - head);
	}
	if (tmp == NULL || ft_strcmp(tmp, cmp_str) == 0)
		ret = false;
	else
		ret = true;
	free_str(&tmp), free_str(&cmp_str);
	return (ret);
}

//		printf("content: %s\n", content);
t_status merge_quote_list(t_list *tokens)
{
	t_status	status;
	char		*content;

	status = STATUS_GENERAL;
	while (tokens && tokens->next)
	{
		content = (char *)tokens->content;
		if (ft_strcmp(content, "\'") == 0 && !exist_double_token(content, '\'') && status == STATUS_GENERAL)
			status = STATUS_QUOTE;
		else if (exist_double_token(content, '\''))
			status = STATUS_GENERAL;
		else if (ft_strcmp(content, "\"") == 0 && !exist_double_token(content, '\"') && status == STATUS_GENERAL)
			status = STATUS_DQUOTE;
		else if (exist_double_token(content, '\"'))
			status = STATUS_GENERAL;
		else if (ft_strcmp(content, "$") == 0 && status != STATUS_QUOTE && tokens->next != NULL)
			status = STATUS_ENV;
		if (status == STATUS_DQUOTE || status == STATUS_QUOTE)
			merge_doutle_string(&tokens);
		else
			tokens = tokens->next;
	}
	return (status);
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
