/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 11:20:08 by sosugimo          #+#    #+#             */
/*   Updated: 2022/05/14 11:20:28 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parser.h"
#include "../includes/execute.h"
#include "../includes/lexer.h"

bool	check_for_copy_expansion(int status, char *data)
{
	if ((status != SINGLE_Q && status != SINGLE_Q * 2)
		&& isenval(data))
		return (true);
	else
		return (false);
}
