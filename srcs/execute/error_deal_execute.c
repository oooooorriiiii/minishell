/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_deal_execute.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 15:41:13 by sosugimo          #+#    #+#             */
/*   Updated: 2022/02/01 16:52:53 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execute.h"

void	malloc_error_exec(char *buf1, char **buf2, t_cmd_args *buf3)
{
	if (!buf1 && !buf2 && !buf3)
	{
		perror("malloc");
		exit(0);
	}
}
