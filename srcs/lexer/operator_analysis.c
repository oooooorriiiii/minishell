/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_analysis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 14:26:16 by ymori             #+#    #+#             */
/*   Updated: 2022/01/30 09:22:29 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "msh_error.h"
#include <errno.h>
#include <signal.h>

void	quote_process_loop(t_list **token_list, char **token, const char quote)
{
	while (true)
	{
		*token_list = (*token_list)->next;
		if (*token_list == NULL)
		{
			ft_putendl_fd("Quote is not closed", STDERR_FILENO);
			exit(1);
		}
		free_set((void **)token, \
					ft_strjoin(*token, (char *)(*token_list)->content));
		if (*(char *)(*token_list)->content == quote)
		{
			*token_list = (*token_list)->next;
			return ;
		}
	}
}

void	quote_process(t_list **token_list, char **token, \
						t_token_list **ret_list)
{
	const char	quote = *(char *)(*token_list)->content;

	free_set((void **)token, \
				ft_strjoin(*token, (char *)(*token_list)->content));
	quote_process_loop(token_list, token, quote);
	if (*token_list == NULL || (*token_list != NULL && \
		ft_strchr("\t\n\v\f\r <>|", *(char *)(*token_list)->content) != NULL))
	{
		token_list_add_back(ret_list, token_listnew(*token, TOKEN));
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

t_status	operator_analysis(t_list **token_list, char *token, \
								t_token_list **ret_list, char *element)
{
	if (*element == '\'' || *element == '\"')
		quote_process(token_list, &token, ret_list);
	else if (ft_strncmp(element, "<<", 2) == 0)
	{
		heredoc_process(token_list, &token, ret_list);
	}
	else if (ft_strncmp(element, ">>", 2) == 0)
	{
		token_list_add_back(ret_list, \
							token_listnew(element, CHAR_DBLGREATER));
		*token_list = (*token_list)->next;
	}
	else if (*element == '<' || *element == '>' || *element == '|')
	{
		token_list_add_back(ret_list, \
							token_listnew(element, *element));
		*token_list = (*token_list)->next;
	}
	return (STATUS_GENERAL);
}
