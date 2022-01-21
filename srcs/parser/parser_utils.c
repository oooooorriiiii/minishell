/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 12:35:40 by sosugimo          #+#    #+#             */
/*   Updated: 2022/01/21 15:25:25 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

bool	term(int toketype, char **bufferptr, t_token_list **curtok)
{
	if (*curtok == NULL)
		return (false);
	printf("[ term ] (*curtok)->val :  %s\n", (*curtok)->val);
	if ((*curtok)->type == toketype)
	{
		if (bufferptr != NULL)
		{
			*bufferptr = malloc(strlen((*curtok)->val) + 1);
			strcpy(*bufferptr, (*curtok)->val);
		}
		*curtok = (*curtok)->next;
		return (true);
	}
	*curtok = (*curtok)->next;
	return (false);
}
