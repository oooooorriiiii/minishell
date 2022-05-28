/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 12:35:40 by sosugimo          #+#    #+#             */
/*   Updated: 2022/05/15 11:44:57 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

void	parse_malloc_errordeal(t_astree *buf1, char *buf2)
{
	if (!buf1 && !buf2)
	{
		perror("parser malloc error");
		exit(0);
	}
}

bool	term(int toketype, char **bufferptr, t_token_list **curtok)
{
	if (*curtok == NULL)
		return (false);
	if ((*curtok)->type == toketype)
	{
		if (bufferptr != NULL)
		{
			*bufferptr = malloc(ft_strlen((*curtok)->val) + 1);
			parse_malloc_errordeal(NULL, *bufferptr);
			ft_strlcpy(*bufferptr, (*curtok)->val,
				ft_strlen((*curtok)->val) + 1);
		}
		*curtok = (*curtok)->next;
		return (true);
	}
	*curtok = (*curtok)->next;
	return (false);
}

bool	trim_x(t_token_list **curtok, t_token_type type)
{
	if (*curtok == NULL)
		return (false);
	if ((*curtok)->type == type)
	{
		*curtok = (*curtok)->next;
		return (true);
	}
	return (false);
}

bool	trim_alloc(t_token_list **curtok, char **bufptr)
{
	if (*curtok == NULL)
		return (false);
	if ((*curtok)->type == TOKEN)
	{
		*bufptr = ft_strdup((*curtok)->val);
		*curtok = (*curtok)->next;
		return (true);
	}
	return (false);
}
