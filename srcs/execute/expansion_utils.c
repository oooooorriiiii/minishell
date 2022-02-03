/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 14:49:49 by sosugimo          #+#    #+#             */
/*   Updated: 2022/02/03 14:52:01 by sosugimo         ###   ########.fr       */
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

int	judge_united_enval(char *str)
{
	int	i;
	int	status;

	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]))
			return (1);
		i++;
	}
	return (0);
}

char	*get_enval(char *split)
{
	char	*enval;

	enval = NULL;
	if (judge_united_enval(split))
		enval = expand_united_enval(split);
	else
		enval = ft_strjoin("", getenv(split));
	return (enval);
}

char	*first_enval(char *str, char *split)
{
	char	*res;

	res = NULL;
	if (str[0] == '$')
	{
		if (judge_united_enval(split))
			res = expand_united_enval(split);
		else
		{
			res = getenv(split);
			if (res)
				res = strdup(res);
		}
	}
	else
		res = strdup(split);
	free(split);
	return (res);
}

char	*expand_enval(char *str)
{
	char	**split;
	char	*enval;
	char	*res;
	int		i;
	char	*tmp;

	i = 1;
	split = ft_split(str, '$');
	res = first_enval(str, split[0]);
	while (split[i])
	{
		enval = get_enval(split[i]);
		if (res && enval)
		{
			tmp = res;
			res = ft_strjoin(tmp, enval);
			double_free(&tmp, &enval);
		}
		else if (enval)
			res = strdup(enval);
		free(split[i]);
		i++;
	}
	free(split);
	return (res);
}
