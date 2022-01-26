/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymori <ymori@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 15:29:32 by ymori             #+#    #+#             */
/*   Updated: 2022/01/27 03:09:18 by ymori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "msh_signal.h"
#include "msh_error.h"
#include "minishell.h"

void	signal_handler_prompt(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("",0);
	rl_redisplay();
}

void	signal_handler_heredoc(int sig)
{
	g_minishell.heredoc_status = sig + 128;
}

int	rl_msh_event_hook_heredoc(void)
{
	if (g_minishell.heredoc_status != 0)
		rl_done = 1;
	return (0);
}

/*
**
*/
void	signal_init(void func1(int), void func2(int), int heredoc_hook(void))
{
	rl_event_hook = heredoc_hook;
	if (signal(SIGINT, func1) == SIG_ERR
		|| signal(SIGQUIT, func2) == SIG_ERR)
		msh_fatal("signal error: ");
	return ;
}
