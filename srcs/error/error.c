/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 03:03:07 by ymori             #+#    #+#             */
/*   Updated: 2022/02/05 20:32:20 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../libft/libft.h"
#include "../includes/execute.h"

void	msh_fatal(char *errmsg)
{
	ft_putstr_fd("fatal: ", STDERR_FILENO);
	if (errmsg == NULL)
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
	else
	{
		if (errno)
		{
			ft_putstr_fd(errmsg, STDERR_FILENO);
			ft_putendl_fd(strerror(errno), 2);
		}
		else
			ft_putendl_fd(errmsg, STDERR_FILENO);
	}
	return ;
}
