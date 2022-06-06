/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 17:07:09 by sosugimo          #+#    #+#             */
/*   Updated: 2022/05/14 18:40:58 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parser.h"
#include "../includes/execute.h"
#include "../includes/lexer.h"

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
	malloc_error_exec(ast_node->szData, NULL, NULL);
	if (expand)
		quote_skip_strcpy(ast_node->szData, expand, *quote);
	else
		ast_node->szData[0] = '\0';
	free(expand);
	return (len);
}

void	copy_one_byone(t_cmd_args *args, t_astree *ast_node, int *i)
{
	int	status;
	int	status2;
	int	len;

	int_init(&status, &status2, &len);
	while (ast_node != NULL && (ast_node->type == NODE_ARGUMENT
			|| ast_node->type == NODE_CMDPATH))
	{
		get_quote_status(&status, ast_node->szData);
		if (check_for_copy_expansion(status, ast_node->szData))
			len = copy_expansion(ast_node, &status2);
		else
			len = quote_skip_strlen(ast_node->szData, &status2);
		if (len > 0)
		{
			args->cmdpath[*i] = (char *)malloc(len + 1);
			malloc_error_exec(args->cmdpath[*i], NULL, NULL);
			quote_skip_strcpy(args->cmdpath[*i], ast_node->szData, status2);
			(*i)++;
		}
		double_reset(&status, &status2);
		ast_node = ast_node->right;
	}
	if (status % 2 == 1)
		g_minishell.exit_status = 2;
}

void	extra_strcpy(t_cmd_args *args, t_astree *ast_node)
{
	int			i;
	t_astree	*tmp_node;

	i = 0;
	tmp_node = ast_node;
	args->cmdpath = (char **)malloc(sizeof(char *)
			* (get_twodim_len(tmp_node) + 1));
	malloc_error_exec(NULL, args->cmdpath, NULL);
	copy_one_byone(args, ast_node, &i);
	args->cmdpath[i] = NULL;
	args->cmdpath_argc = i;
}
