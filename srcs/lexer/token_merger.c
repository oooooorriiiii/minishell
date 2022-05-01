#include "lexer.h"
#include "msh_error.h"
#include "utils.h"

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

/*
 *printf("content: %s\n", content);
 *		else if (ft_strcmp(content, "$") == 0 && \
 *					status != STATUS_QUOTE \
 *					&& tokens->next != NULL)
 *			status = STATUS_ENV;
*/
t_status	merge_quote_list(t_list *tokens)
{
	t_status	status;
	char		*content;

	status = STATUS_GENERAL;
	while (tokens && tokens->next)
	{
		content = (char *)tokens->content;
		if (ft_strcmp(content, "\'") == 0 && !exist_double_token(content, '\'') \
			&& status == STATUS_GENERAL)
			status = STATUS_QUOTE;
		else if (exist_double_token(content, '\''))
			status = STATUS_GENERAL;
		else if (ft_strcmp(content, "\"") == 0 && !exist_double_token(content, '\"') \
					&& status == STATUS_GENERAL)
			status = STATUS_DQUOTE;
		else if (exist_double_token(content, '\"'))
			status = STATUS_GENERAL;
		if (status == STATUS_DQUOTE || status == STATUS_QUOTE)
			merge_doutle_string(&tokens);
		else
			tokens = tokens->next;
	}
	return (status);
}
