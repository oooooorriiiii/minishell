/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 22:23:51 by ymori             #+#    #+#             */
/*   Updated: 2022/02/04 00:25:33 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "msh_error.h"
#include <stdio.h>

bool	is_space_string(char *s)
{
	while (ft_isblank(*s))
		s++;
	return (!*s);
}

//	print_token_list(ret_list);// DEBUG
t_status	lexcal_analysis(t_list *init_token_list, t_lexer **lex_list)
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
			operetor_analysis(&init_token_list, token, &ret_list, element);
		else
			literal_process(&init_token_list, &token, &ret_list);
	}
	free(token);
	*lex_list = lexer_new(ret_list);
	return (STATUS_GENERAL);
}

/*
**
*/
//	list_print(init_token_list);
//	puts("*****");
t_status	lexer(char *original_line, t_lexer **lex_list)
{
	t_list		*init_token_list;
	t_status	status;

	if (original_line == NULL || lex_list == NULL)
		msh_fatal("lexer error");
	if (is_space_string(original_line))
	{
		*lex_list = lexer_new(NULL);
		return (STATUS_WHITESPACE);
	}
	init_token_list = token_split_to_list(original_line);
	status = lexcal_analysis(init_token_list, lex_list);
	ft_lstclear(&init_token_list, free);
	return (status);
}
