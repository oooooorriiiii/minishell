/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymori <ymori@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 12:09:20 by ymori             #+#    #+#             */
/*   Updated: 2022/01/20 13:48:35 by ymori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

bool	is_quote(char c)
{
	if (c == SINGLE_QUOTE || c == DOUBLE_QUOTE)
		return (true);
	return (false);
}

bool	is_operator(char *element)
{
	if (!ft_strncmp(element, "|", 1) || !ft_strncmp(element, ">>", 2) || \
			!ft_strncmp(element, "<<", 2) || !ft_strncmp(element, ">", 1) || \
			!ft_strncmp(element, "<", 1))
		return (true);
	return (false);
}

int	ft_isblank(int c)
{
	if (c == ' ' || c == '\t')
	{
		return (1);
	}
	return (0);
}
