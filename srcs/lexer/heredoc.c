/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymori <ymori@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 03:24:44 by ymori             #+#    #+#             */
/*   Updated: 2022/01/27 03:30:03 by ymori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "msh_signal.h"
#include "msh_error.h"

static void	list_skip(t_list **token_list)
{
	if (token_list == NULL)
		msh_fatal("Invalid argument");
	while (*token_list)
	{
		if (!ft_strchr("\t\n\v\f\r \'\"", *(char *)(*token_list)->content))
			return ;
		*token_list = (*token_list)->next;
	}
	return ;
}

static char	*heredoc_readline(char *heredoc)
{
	char	*read;
	int		flag;
	char	*token;

	g_minishell.heredoc_status = 0;
	flag = 0;
	token = ft_strdup("");
	signal_init(signal_handler_heredoc, SIG_IGN, rl_msh_event_hook_heredoc);
	while (true)
	{
		read = readline("heredoc> ");
		if (g_minishell.heredoc_status != 0 || read == NULL)
		{
			free_set((void **)&token, ft_strdup(""));
			break ;
		}
		if (ft_strcmp(read, heredoc) == 0)
			break ;
		free_set((void **)&token, ft_strjoin(token, read));
		free_set((void **)&token, ft_strjoin(token, "\n"));
		free(read);
		flag++;
	}
	free_set((void **)&read, NULL);
	signal_init(signal_handler_prompt, SIG_IGN, NULL);
	return (token);
}

t_status	heredoc_process(t_list **token_list, char **token, \
							t_token_list **ret_list)
{
	token_list_add_back(ret_list, token_listnew("<<", CHAR_DBLLESSER));
	*token_list = (*token_list)->next;
	list_skip(token_list);
	if (*token_list == NULL)
		return (STATUS_ERROR);
	free_set((void **)token_list, heredoc_readline((*token_list)->content));
	token_list_add_back(ret_list, token_listnew(*token, TOKEN));
	free_set((void **)token_list, ft_strdup(""));
	*token_list = (*token_list)->next;
	return (STATUS_GENERAL);
}
