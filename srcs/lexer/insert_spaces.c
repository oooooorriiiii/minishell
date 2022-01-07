/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_spaces.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymori <ymori@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 12:39:13 by ymori             #+#    #+#             */
/*   Updated: 2022/01/07 23:44:06 by ymori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdio.h>

/*
** Return True if the same token exists in the following lines.
** "line" is trimmed.
*/
static bool	exist_closing_token(char **line, char token)
{
	char	*current_char;

	current_char = *line;
	current_char++;
	while (*current_char)
	{
		if (*current_char == token)
		{
			*line = current_char;
			return (true);
		}
		current_char++;
	}
	return (false);
}

int		ft_isblank(int c)
{
	if (c == ' ' || c == '\t')
	{
		return (1);
	}
	return (0);
}

static bool	is_operator(char *value)
{
	if (!ft_strncmp(value, "|", 1) || !ft_strncmp(value, ">>", 2) || !ft_strncmp(value, "<<", 2) || !ft_strncmp(value, ">", 1) || !ft_strncmp(value, "<", 1))
		return (true);
	return (false);
}

bool	between_quotes(char **line)
{
	char	*current_char;

	current_char = *line;
	if (is_quote(*current_char) && exist_closing_token(line, *current_char))
		return (true);
	return (false);
}

void	insert_spaces(char **line)
{
	char	*current_line;
	char	*copied_init_lint;

	current_line = *line;
	copied_init_lint = *line;
	while (current_line && *current_line)
	{
		// TODO: Ignore if it is between quotes.
	}
}
