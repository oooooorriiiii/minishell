/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 12:35:40 by sosugimo          #+#    #+#             */
/*   Updated: 2022/01/18 00:49:41 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	term(int toketype, char **bufferptr, tok_t **curtok)
{
	if (*curtok == NULL)
		return (false);
	if ((*curtok)->type == toketype)
	{
		if (bufferptr != NULL)
		{
			*bufferptr = malloc(strlen((*curtok)->data) + 1);
			strcpy(*bufferptr, (*curtok)->data);
		}
		*curtok = (*curtok)->next;
		return (true);
	}
	*curtok = (*curtok)->next;
	return (false);
}
