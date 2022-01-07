/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_spaces.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymori <ymori@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 12:39:13 by ymori             #+#    #+#             */
/*   Updated: 2022/01/07 14:55:25 by ymori            ###   ########.fr       */
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

bool	between_quotes(char **line)
{
	char	*current_char;

	current_char = *line;
	// TODO: is only operator ??
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
		if (between_quotes(&current_line))
		{
			current_line++;
			continue ;
		}
	}
}
