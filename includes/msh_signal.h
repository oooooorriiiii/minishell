/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_signal.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 02:55:52 by ymori             #+#    #+#             */
/*   Updated: 2022/01/29 18:08:00 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_SIGNAL_H
# define MSH_SIGNAL_H

# include <signal.h>

# define MSH_SIG_PROMPT	4242

void	signal_handler_prompt(int sig);
void	signal_handler_heredoc(int sig);
int		rl_msh_event_hook_heredoc(void);
void	signal_init(void func1(int), void func2(int), int heredoc_hook(void));
void	msh_signal(int signo);

#endif
