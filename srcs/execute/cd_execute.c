/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 16:11:23 by sosugimo          #+#    #+#             */
/*   Updated: 2022/01/26 20:02:25 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execute.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/wait.h>
#include <pwd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <signal.h>

void	execute_cd(t_cmd_args *args)
{
	if (args->cmdpath_argc == 1)
		chdir(getenv("HOME"));
	else if (args->cmdpath_argc > 2)
		printf("cd: Too many arguments\n");
	else
	{
		if (chdir(args->cmdpath[1]) != 0)
			perror(args->cmdpath[1]);
	}

	// -------------- to check current dir
	char	path_name[512];
	getcwd(path_name, 512);
	printf("current dir : %s\n", path_name);
}

