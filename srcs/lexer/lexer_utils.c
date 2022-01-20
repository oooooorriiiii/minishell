/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymori <ymori@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 13:49:50 by ymori             #+#    #+#             */
/*   Updated: 2022/01/20 13:53:04 by ymori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_lexer	*lexer_new(t_token_list *token_list)
{
	t_lexer	*lexer;

	lexer = malloc(sizeof(t_lexer));
	// lexer->len = ft_lstsize(token_list);
	lexer->len = 4242;
	lexer->list = token_list;
	return (lexer);
}

void	lexer_free(t_lexer **lexer)
{
	token_list_clear(&((*lexer)->list));
	free(*lexer);
	*lexer = NULL;
}
