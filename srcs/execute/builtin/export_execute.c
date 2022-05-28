/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_execute.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 16:11:50 by sosugimo          #+#    #+#             */
/*   Updated: 2022/02/09 15:05:33 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "msh_error.h"
#include "msh_env.h"
#include "utils.h"

static void	restore_arg(char *sep, bool append_flag)
{
	if (sep)
	{
		*sep = '=';
		if (append_flag == true)
			*(sep - 1) = '+';
	}
}

/*
 * case 1)
 * KEY=VALUE
 * -> append_flag = false
 * In the case of "=", the operation to update all variables is executed.
 *
 * case 2)
 * KEY+=VALUE
 * -> append_flag = true
 * In the case of "+=", the operation to append is executed.
 *
 * KEY=VALUE
 * arg:    KEY=VALUE
 * *sep:   =VALUE
 * *value: VALUE
 */
static int	separate_arg(char *arg, char **sep, char **value)
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
	return (append_flag);
}

/*
 *
 */
static int	store_env(char **cmdpath)
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
		if (satisfy_env_name_rule(cmdpath[i]))
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

void	execute_export(t_cmd_args *args)
{
	char	**env_arr;
	int		status;

	status = EXIT_SUCCESS;
	if (!(args->cmdpath[1]))
	{
		env_arr = gen_env_str(g_minishell.env);
		print_export(env_arr);
		free_str_arr(&env_arr);
	}
	else
		status = store_env(args->cmdpath);
	g_minishell.exit_status = status;
}
