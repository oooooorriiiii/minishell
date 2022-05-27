#include "parser.h"
#include "expansion.h"
#include "msh_error.h"

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

void	expansion_dollar_heredoc(char *content, t_list *list)
{
	if (ft_strcmp(content, "$") == 0 \
		&& list->next != NULL \
		&& ft_strpbrk((const char *)list->next->content, " \t\n\v\f\r\"") \
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
			free_set((void **) &astree->szData, \
			heredoc_expansion(astree->szData));
		else
			free_set((void **) &astree->szData, \
			general_expansion(astree->szData));
	}
	expansion(astree->right);
	expansion(astree->left);
}
