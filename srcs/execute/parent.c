/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 12:43:29 by sosugimo          #+#    #+#             */
/*   Updated: 2022/01/27 13:02:16 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static int	execute_in_parent(t_command *command, char **args)
{
	if (setup_redirects(command) == FALSE)
		return (EXIT_FAILURE);
	if (dup_redirects(command, TRUE) == FALSE)
		return (EXIT_FAILURE);
	return (exec_builtin(args));
}
