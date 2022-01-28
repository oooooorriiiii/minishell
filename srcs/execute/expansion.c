/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 17:07:09 by sosugimo          #+#    #+#             */
/*   Updated: 2022/01/28 17:42:05 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

# define single_q 1
# define double_q 10

int	quote_skip_strlen(char *arguments, int *quote, int *param)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (arguments[i])
	{
		if (arguments[i] == '\'' && (!*quote || *quote == single_q))
		{
			*quote += single_q;
			*param = single_q;
		}
		else if (arguments[i] == '\"' && (!*quote || *quote == double_q))
		{
			*quote += double_q;
			*param = double_q;
		}
		else
			res++;
		if (*quote >= single_q * 2 || *quote >= double_q * 2)
			*quote = 0;
		i++;
	}
	return (res);
}

void	quote_skip_strcpy(char *dst, char *src, int quote)
{
	int		i;
	int		skip;
	char	*expand;

	i = 0;
	skip = 0;
	while (src[j])
	{
		if (src[j] == '\'' && quote == single_q && skip < 2)
		{
			skip++;
			j++;
		}
		else if (src[j] == '\"' && quote == double_q && skip < 2)
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

ssize_t	expand_enval(char **dst, char *src)
{
	char	**split;
	char	*enval;
	char	*tmp;
	int		i;

	i = 1;
	split = ft_split(src, '$');
	*dst = getenv(split[0]);
	if (*dst == NULL)
		*dst = split[0];
	while (split[i])
	{
		enval = getenv(split[i]);
		if (enval != NULL)
			ft_strlcat(*dst, enval, strlen(*dst) + strlen(enval) + 1);
		i++;
	}
	return (ft_strlen(*dst));
}

void	extra_strcpy(t_cmd_args *args, t_astree *ast_node)
{
	int			i;
	int			quote;
	int			param;
	int			len;
	char		*expand;

	i = 0;
	quote = 0;
	while (ast_node != NULL && (ast_node->type == NODE_ARGUMENT
			|| ast_node->type == NODE_CMDPATH))
	{
		len = quote_skip_strlen(ast_node->szData, &quote, &param);
		if (param != single_q && isenval(ast_node->szData))
		{
			expand = expand_enval(ast_node->szData);
			len = quote_skip_strlen(expand, &quote, &param);
			free(ast_node->szData);
			ast_node->szData = expand;
		}
		args->cmdpath[i] = (char *)malloc(len + 1);
		quote_skip_strcpy(args->cmdpath[i], ast_node->szData, param);
		ast_node = ast_node->right;
		i++;
	}
	args->cmdpath[i] = NULL;
	args->cmdpath_argc = i;
}
