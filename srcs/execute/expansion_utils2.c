/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 14:49:40 by sosugimo          #+#    #+#             */
/*   Updated: 2022/02/04 18:59:25 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parser.h"
#include "../includes/execute.h"
#include "../includes/lexer.h"

int	quote_skip_strlen(char *arguments, int *quote)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (arguments[i])
	{
		if (arguments[i] == '\'' && (!*quote || *quote == SINGLE_Q))
			*quote += SINGLE_Q;
		else if (arguments[i] == '\"' && (!*quote || *quote == DOUBLE_Q))
			*quote += DOUBLE_Q;
		else
			len++;
		i++;
	}
	return (len);
}

void	quote_skip_strcpy(char *dst, char *src, int quote)
{
	int		i;
	int		j;
	int		skip;

	i = 0;
	j = 0;
	skip = 0;
	while (src[j])
	{
		if (skip < 2 && ((src[j] == '\'' && (quote == SINGLE_Q
						|| quote == SINGLE_Q * 2)) || (src[j] == '\"'
					&& (quote == DOUBLE_Q || quote == DOUBLE_Q * 2))))
		{
			skip++;
			j++;
		}
		else
		{
			if (src[j])
				dst[i] = src[j];
			i++;
			j++;
		}
	}
	dst[i] = '\0';
}

char	**split_non_alnum(char *str)
{
	char	**split;
	int		enval_len;
	int		i;

	split = (char **)malloc(sizeof(char *) * 3);
	malloc_error_exec(NULL, split, NULL);
	enval_len = 0;
	i = 0;
	while (str[enval_len])
	{
		if (!ft_isalnum(str[enval_len]))
			break ;
		enval_len++;
	}
	split[0] = (char *)malloc(sizeof(char) * (enval_len + 1));
	malloc_error_exec(split[0], NULL, NULL);
	ft_strlcpy(split[0], str, enval_len + 1);
	str += enval_len;
	split[1] = (char *)malloc(sizeof(char) * (strlen(str) + 1));
	malloc_error_exec(split[1], NULL, NULL);
	ft_strlcpy(split[1], str, strlen(str) + 1);
	split[2] = NULL;
	return (split);
}
