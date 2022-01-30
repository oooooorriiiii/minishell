/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 17:07:09 by sosugimo          #+#    #+#             */
/*   Updated: 2022/01/30 15:42:22 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parser.h"
#include "../includes/execute.h"
#include "../includes/lexer.h"

int	quote_skip_strlen(char *arguments, int *quote)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (arguments[i])
	{
		if (arguments[i] == '\'' && (!*quote || *quote == SINGLE_Q))
			*quote += SINGLE_Q;
		else if (arguments[i] == '\"' && (!*quote || *quote == DOUBLE_Q))
			*quote += DOUBLE_Q;
		else
			res++;
		if (*quote >= SINGLE_Q * 2 || *quote >= DOUBLE_Q * 2)
			*quote = 0;
		i++;
	}
	return (res);
}

void	quote_skip_strcpy(char *dst, char *src, int quote)
{
	int		i;
	int		j;
	int		skip;
	char	*expand;

	i = 0;
	j = 0;
	skip = 0;
	while (src[j])
	{
		if (src[j] == '\'' && quote == SINGLE_Q && skip < 2)
		{
			skip++;
			j++;
		}
		else if (src[j] == '\"' && quote == DOUBLE_Q && skip < 2)
		{
			skip++;
			j++;
		}
		else
		{
			dst[i] = src[j];
			i++;
			j++;
		}
	}
}

int	isenval(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

char	*first_enval(char *str, char *split)
{
	char	*res;

	res = NULL;
	if (str[0] == '$')
	{
		res = getenv(split);
		if (res)
			res = ft_strdup(res);
	}
	else
		res = ft_strdup(split);
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
		enval = getenv(split[i]);
		free(split[i]);
		if (res && enval)
		{
			tmp = res;
			res = ft_strjoin(tmp, enval);
			free(tmp);
		}
		else if (enval)
			res = ft_strdup(enval);
		i++;
	}
	free(split);
	return (res);
}

void	get_quote_status(int *status, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' && (*status == 0 || *status == SINGLE_Q))
			*status += SINGLE_Q;
		else if (str[i] == '\"' && (*status == 0 || *status == DOUBLE_Q))
			*status += DOUBLE_Q;
		i++;
	}
}

void	reset_status(int *status)
{
	if (*status == SINGLE_Q * 2 || *status == DOUBLE_Q * 2)
		*status = 0;
}

void	extra_strcpy(t_cmd_args *args, t_astree *ast_node)
{
	int			i;
	int			quote;
	int			len;
	char		*expand;
	int			status;

	i = 0;
	quote = 0;
	status = 0;
	printf("This needs EXPANSION\n");
	while (ast_node != NULL && (ast_node->type == NODE_ARGUMENT
			|| ast_node->type == NODE_CMDPATH))
	{
		get_quote_status(&status, ast_node->szData);
		len = quote_skip_strlen(ast_node->szData, &quote);
		if ((status != SINGLE_Q || status != SINGLE_Q * 2)
			&& isenval(ast_node->szData))
		{
			expand = expand_enval(ast_node->szData);
			len = quote_skip_strlen(expand, &quote);
			free(ast_node->szData);
			ast_node->szData = expand;
		}
		reset_status(&status);
		args->cmdpath[i] = (char *)malloc(len + 1);
		quote_skip_strcpy(args->cmdpath[i], ast_node->szData, quote);
		ast_node = ast_node->right;
		i++;
	}
	args->cmdpath[i] = NULL;
	args->cmdpath_argc = i;
	// i = 0;
	// while (args->cmdpath[i])
	// {
	// 	printf("args->cmdpath[%d]   :    %s\n", i, args->cmdpath[i]);
	// 	i++;
	// }
}
