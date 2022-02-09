/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 12:43:29 by sosugimo          #+#    #+#             */
/*   Updated: 2022/02/05 18:49:31 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execute.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void	execute_in_parent(t_cmd_args *args)
{
	int	backup;

	backup = 0;
	dupfor_redirection(args, &backup);
	execute_command_struct(args);
	close_fdbackup(args, &backup);
}
