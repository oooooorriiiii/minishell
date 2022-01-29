/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_execute.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 16:11:50 by sosugimo          #+#    #+#             */
/*   Updated: 2022/01/24 13:39:22 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execute.h"
#include "../libft/libft.h"
#include "msh_error.h"
#include "msh_env.h"
#include "utils.h"

static bool		satisfy_name_rule(*key)
{
	size_t	i;

	i = 0;
	if (key[i] != '_' && !ft_isalpha(key[i]))
		return (false);
	i++;
	while (key[i])
	{
		if (key[i] != '_' && !ft_isalnum(key[i]))
			return (false);
		i++;
	}
	return (true);
}

static void		restore_arg(char *sep, bool append_flag)
{
	if (sep)
	{
		*sep = '=';
		if (append_flag == true)
			*(sep - 1) = '+';
	}
}

static int		separate_arg(char *arg, char **sep, char **value)
{
	bool	append_flag;

	append_flag = false;
	*sep = ft_strchr(arg, '=');
	if (*sep)
	{
		**sep = 0;
		if (*sep != arg && *(*sep - 1) == '+')
		{
			*(*sep - 1) = '\0';
			append_flag = true;
		}
		*value = *sep + 1;
	}
	else
		*value = NULL;
}

static int		store_env(char **cmdpath)
{
	size_t	i;
	int		status;
	char	*value;
	char	*sep;
	bool	append_flag;

	status = EXIT_SUCCESS;
	i = 1;
	value = NULL;
	while (cmdpath[i])
	{
		append_flag = false;
		append_flag = separate_arg(cmdpath[i], &sep, &value);
		if (satisfy_name_rule(cmdpath[i]))
			update_env_val(cmdpath[i], value, true, append_flag);
		else
		{
			restore_arg(sep, append_flag);
			msh_fatal("invalid name error in export");
			status = EXIT_FAILURE;
		}
		i++;
	}
	return (status);
}

void	print_export(char **env_arr)
{
	while (*env_arr)
	{
		printf("declare -x ");
		printf("%s\n", *env_arr++);
	}
}

// return exit status ??
void			execute_export(t_cmd_args *args)
{
	char	**env_arr;
	int		status;

	status = EXIT_SUCCESS;
	printf(" execute_export \n"); // DEBUG
	if (!(args->cmdpath[1]))
	{
		env_arr = msh_get_envlist(g_minishell.env);
		print_export(env_arr);
		free_str(env_arr);
	}
	else
		status = store_env(args->cmdpath[1]);
	return ;
}
