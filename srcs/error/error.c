/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymori <ymori@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 03:03:07 by ymori             #+#    #+#             */
/*   Updated: 2022/01/27 03:14:47 by ymori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../libft/libft.h"

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
	exit(1);
}
