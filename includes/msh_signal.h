/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_signal.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymori <ymori@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 02:55:52 by ymori             #+#    #+#             */
/*   Updated: 2022/01/27 03:01:01 by ymori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_SIGNAL_H
# define MSH_SIGNAL_H

#include <signal.h>

void	signal_handler_prompt(int sig);
void	signal_handler_heredoc(int sig);
int		rl_msh_event_hook_heredoc(void);
void	signal_init(void func1(int), void func2(int), int heredoc_hook(void));

#endif
