/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 14:49:49 by sosugimo          #+#    #+#             */
/*   Updated: 2022/05/14 10:58:59 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parser.h"
#include "../includes/execute.h"
#include "../includes/lexer.h"

char	*expand_united_enval(char *str)
{
	char	**split;
	char	*enval;
	char	*res;
	char	*exit_status;

	if (str[0] == '?')
	{
		exit_status = ft_itoa(g_minishell.exit_status);
		res = ft_strjoin(exit_status, ++str);
		free(exit_status);
		return (res);
	}
	split = split_non_alnum(str);
	enval = getenv(split[0]);
	if (enval)
		res = ft_strjoin(enval, split[1]);
	else
		res = ft_strjoin("", split[1]);
	free(split[0]);
	free(split[1]);
	free(split[2]);
	free(split);
	return (res);
}

char	*get_enval(char *split)
{
	char	*enval;

	enval = NULL;
	if (!strcmp(split, "?"))
		enval = ft_itoa(g_minishell.exit_status);
	else if (judge_united_enval(split))
		enval = expand_united_enval(split);
	else
		enval = ft_strjoin("", getenv(split));
	return (enval);
}

bool	next_to_envalmark(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] && ft_isalnum(str[i + 1]))
			return (true);
		if (str[i] == '$' && str[i + 1] && str[i + 1] == '?')
			return (true);
		i++;
	}
	return (false);
}

void	join_splitted(char **res, char **enval)
{
	char	*tmp;

	tmp = *res;
	*res = ft_strjoin(tmp, *enval);
	double_free(&tmp, enval);
}

char	*expand_enval(char *str)
{
	char	**split;
	char	*enval;
	char	*res;
	int		i;

	i = 1;
	if (!next_to_envalmark(str))
		return (strdup(str));
	split = ft_split(str, '$');
	res = first_enval(str, split[0]);
	while (split[i])
	{
		enval = get_enval(split[i]);
		if (res && enval)
			join_splitted(&res, &enval);
		else if (enval)
			res = strdup(enval);
		free(split[i]);
		i++;
	}
	free(split);
	return (res);
}
