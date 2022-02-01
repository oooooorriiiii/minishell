/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 17:07:09 by sosugimo          #+#    #+#             */
/*   Updated: 2022/02/01 02:13:32 by sosugimo         ###   ########.fr       */
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

char	**split_non_alnum(char *str)
{
	char	**split;
	int		enval_len;
	int		i;

	split = (char **)malloc(sizeof(char *) * 3);
	enval_len = 0;
	i = 0;
	while (str[enval_len])
	{
		if (!ft_isalnum(str[enval_len]))
			break ;
		enval_len++;
	}
	split[0] = (char *)malloc(sizeof(char) * (enval_len + 1));
	ft_strlcpy(split[0], str, enval_len + 1);
	str += enval_len;
	split[1] = (char *)malloc(sizeof(char) * (strlen(str) + 1));
	ft_strlcpy(split[1], str, strlen(str) + 1);
	split[2] = NULL;
	return (split);
}

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

void	double_free(char **buf1, char **buf2)
{
	free(*buf1);
	free(*buf2);
}

char	*first_enval(char *str ,char *split)
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

int	get_twodim_len(t_astree *ast_node)
{
	int		len;
	int		status;
	char	*buf;

	len = 0;
	status = 0;
	buf = NULL;
	while (ast_node != NULL && (ast_node->type == NODE_ARGUMENT
			|| ast_node->type == NODE_CMDPATH))
	{
		get_quote_status(&status, ast_node->szData);
		buf = expand_enval(ast_node->szData);
		if (!((status == DOUBLE_Q || status == DOUBLE_Q * 2 || status == 0)
				&& isenval(ast_node->szData) && !buf))
			len++;
		free(buf);
		reset_status(&status);
		ast_node = ast_node->right;
	}
	reset_status(&status);
	return (len);
}

int	copy_expansion(t_astree *ast_node, int *quote)
{
	int		len;
	char	*expand;

	len = 0;
	expand = expand_enval(ast_node->szData);
	if (expand)
		len = quote_skip_strlen(expand, quote);
	free(ast_node->szData);
	ast_node->szData = (char *)malloc(sizeof(char) * (len + 1));
	if (expand)
		quote_skip_strcpy(ast_node->szData, expand, *quote);
	else
		ast_node->szData[0] = '\0';
	free(expand);
	return (len);
}

void double_reset(int *status, int *status2)
{
	reset_status(status);
	reset_status(status2);
}

void	copy_one_byone(t_cmd_args *args, t_astree *ast_node, int *i)
{
	int	status;
	int	status2;
	int	len;

	status = 0;
	status2 = 0;
	len = 0;
	while (ast_node != NULL && (ast_node->type == NODE_ARGUMENT
			|| ast_node->type == NODE_CMDPATH))
	{
		get_quote_status(&status, ast_node->szData);
		if ((status != SINGLE_Q && status != SINGLE_Q * 2)
			&& isenval(ast_node->szData))
			len = copy_expansion(ast_node, &status2);
		else
			len = quote_skip_strlen(ast_node->szData, &status2);
		if (len > 0)
		{
			args->cmdpath[*i] = (char *)malloc(len + 1);
			quote_skip_strcpy(args->cmdpath[*i], ast_node->szData, status2);
			(*i)++;
		}
		double_reset(&status, &status2);
		ast_node = ast_node->right;
	}
}

void	extra_strcpy(t_cmd_args *args, t_astree *ast_node)
{
	int			i;
	t_astree	*tmp_node;

	i = 0;
	tmp_node = ast_node;
	args->cmdpath = (char **)malloc(sizeof(char *)
			* (get_twodim_len(tmp_node) + 1));
	copy_one_byone(args, ast_node, &i);
	args->cmdpath[i] = NULL;
	args->cmdpath_argc = i;
}
