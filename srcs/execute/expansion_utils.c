/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 14:49:49 by sosugimo          #+#    #+#             */
/*   Updated: 2022/02/04 19:22:26 by sosugimo         ###   ########.fr       */
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
		if (!ft_isalnum(str[i]) && str[i] != '?')
			return (1);
		i++;
	}
	return (0);
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
			if (!strcmp(split, "?"))
				res = ft_itoa(g_minishell.exit_status);
			else
			{
				res = getenv(split);
				if (res)
					res = strdup(res);
			}
		}
	}
	else
		res = strdup(split);
	free(split);
	return (res);
}

//?の次がalnumかどうか
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

// char	*get_exit_status(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '$' && str[i + 1] && str[i + 1] == '?')
// 			return (ft_itoa(g_minishell.exit_status));
// 		i++;
// 	}
// 	return (NULL);
// }

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
