#include "parser.h"
#include "msh_error.h"

char	*ft_strpbrk(const char *s1, const char *s2)
{
	const char	*t = s2;

	while (*s1)
	{
		while (*t)
		{
			if (*t == *s1)
				return ((char *)s1);
			t++;
		}
		s1++;
	}
	return (NULL);
}

char	*expansion_env(char *content)
{
	char	*ret;

	if (ft_strcmp(content, "?") == 0)
	{
		if (g_minishell.heredoc_status != 0)
			ret = ft_itoa(g_minishell.heredoc_status);
		else
			ret = ft_itoa(g_minishell.exit_status);
		g_minishell.heredoc_status = 0;
	}
	else
	{
		ret = get_env_value(content);
		if (ret == NULL)
			ret = "";
		ret = ft_strdup(ret);
	}
	return (ret);
}

void	expansion_dollar_general(char *content, t_status status, t_list *list)
{
	if (ft_strcmp(content, "$") == 0 \
		&& status != STATUS_QUOTE \
		&& list->next != NULL \
		&& ft_strpbrk((const char *)list->next->content, " \t\n\v\f\r\"\'") \
			== NULL)
	{
		free_set(&list->content, NULL);
		list = list->next;
		free_set(&list->content, expansion_env((char *)list->content));
	}
}

void	expansion_quotes_dollar(char *content, t_status *status, t_list *list)
{
	if (ft_strcmp(content, "\'") == 0 && *status == STATUS_GENERAL)
	{
		free_set(&list->content, NULL);
		*status = STATUS_QUOTE;
	}
	else if (ft_strcmp(content, "\'") == 0 && *status== STATUS_QUOTE)
	{
		free_set(&list->content, NULL);
		*status = STATUS_GENERAL;
	}
	else if (ft_strcmp(content, "\"") == 0 && *status == STATUS_GENERAL)
	{
		free_set(&list->content, NULL);
		*status = STATUS_DQUOTE;
	}
	else if (ft_strcmp(content, "\"") == 0 && *status == STATUS_DQUOTE)
	{
		free_set(&list->content, NULL);
		*status = STATUS_GENERAL;
	}
	else
	{
		expansion_dollar_general(content, *status, list);
	}
}

t_list	*split_to_list(char *line)
{
	const char	*sep_char = " \t\n\v\f\r\?\'\"$";
	t_list		*new_list;
	char		*head;

	new_list = NULL;
	while (*line != '\0')
	{
		if (ft_strchr(sep_char, *line) != NULL)
		{
			ft_lstadd_back(&new_list, ft_lstnew(ft_substr(line, 0, 1)));
			line++;
		}
		else
		{
			head = line;
			while (ft_strchr(sep_char, *line) == NULL)
				line++;
			ft_lstadd_back(&new_list, \
				ft_lstnew(ft_substr(head, 0, line - head)));
		}
	}
	return (new_list);
}

char	*list_to_str(t_list *list)
{
	char	*ret_str;

	if (list == NULL)
		msh_fatal("expansion");
	if ((char *)list->content != NULL)
		ret_str = ft_strdup((char *)list->content);
	else
		ret_str = ft_strdup("");
	while (list->next)
	{
		free_set((void **)&ret_str, ft_strjoin(ret_str, ""));
		if ((char *)list->next->content != NULL)
			free_set((void **)&ret_str, \
			ft_strjoin(ret_str, (char *)list->next->content));
					 list = list->next;
	}
	return (ret_str);
}

//printf("before: expansion---\n"); // D
//list_print(sep_data); // D
//printf("before: expansion---\n"); // D
//printf("after: expansion---\n"); // D
//list_print(sep_data); // D
//printf("after: expansion---\n"); // D
char	*general_expansion(char *data)
{
	t_list		*sep_data;
	t_list		*head;
	char		*ret;
	char		*content;
	t_status	status;

	printf("data: %s\n", data); // D
	status = STATUS_GENERAL;
	if (data == NULL)
		msh_fatal("expamsion");
	if (*data == '\0')
		return (ft_strdup(data));
	sep_data = split_to_list(data);
	head = sep_data;
	while (sep_data)
	{
		content = (char *)sep_data->content;
		expansion_quotes_dollar(content, &status, sep_data);
		sep_data = sep_data->next;
	}
	sep_data = head;
	ret = list_to_str(sep_data);
	ft_lstclear(&sep_data, free);
	return (ret);
}

void	expansion_dollar_heredoc(char *content, t_list *list)
{
	if (ft_strcmp(content, "$") == 0 \
		&& list->next != NULL \
		&& ft_strpbrk((const char *)list->next->content, " \t\n\v\f\r\"")
			== NULL)
	{
		free_set(&list->content, NULL);
		list = list->next;
		free_set(&list->content, expansion_env((char *)list->content));
	}
}

char	*heredoc_expansion(char *data)
{
	t_list	*sep_data;
	t_list	*head;
	char	*ret;
	char	*content;

	if (data == NULL)
		msh_fatal("expansion");
	if (*data == '\0')
		return (ft_strdup(data));
	sep_data = split_to_list(data);
	head = sep_data;
	while (sep_data)
	{
		content = (char *)sep_data->content;
		expansion_dollar_heredoc(content, sep_data);
		sep_data = sep_data->next;
	}
	sep_data = head;
	ret = list_to_str(sep_data);
	ft_lstclear(&sep_data, free);
	return (ret);
}

void	expansion(t_astree *astree)
{
	if (astree == NULL)
		return ;
	if (astree->type & ELIGIBLE_EXPANSION)
	{
		if (astree->type & NODE_REDIRECT_D_IN)
			free_set((void **) &astree->szData, heredoc_expansion(astree->szData));
		else
			free_set((void **) &astree->szData, general_expansion(astree->szData));
	}
	expansion(astree->right);
	expansion(astree->left);
}
