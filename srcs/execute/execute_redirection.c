/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymori <ymori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 22:07:21 by ymori             #+#    #+#             */
/*   Updated: 2022/05/28 22:07:21 by ymori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

t_exec_result	redirection_in(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	open_error_handle(fd);
	if (fd == -1)
		return (e_failure);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (e_success);
}

t_exec_result	redirection_out(char *filename)
{
	int	fd;
	int	oflag;

	oflag = O_WRONLY | O_CREAT | O_TRUNC;
	fd = open(filename, oflag, 0644);
	open_error_handle(fd);
	if (fd == -1)
		return (e_failure);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (e_success);
}

t_exec_result	redirection_d_out(char *filename)
{
	int	fd;
	int	oflag;

	oflag = O_WRONLY | O_CREAT | O_APPEND;
	fd = open(filename, oflag, 0644);
	open_error_handle(fd);
	if (fd == -1)
		return (e_failure);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (e_success);
}

t_exec_result	execute_redirection(t_astree *cmdNode, t_cmd_args *args)
{
	t_exec_result	ret;

	(void)args;
	ret = e_success;
	while (cmdNode && (cmdNode->type & NODE_REDIRECTION_LIST))
	{
		if (cmdNode->left->type & NODE_REDIRECT_IN)
			ret = redirection_in(cmdNode->left->szData);
		else if (cmdNode->left->type & NODE_REDIRECT_OUT)
			ret = redirection_out(cmdNode->left->szData);
		else if (cmdNode->left->type & NODE_REDIRECT_D_IN)
			ret = handle_heredoc(cmdNode->left->szData);
		else if (cmdNode->left->type & NODE_REDIRECT_D_OUT)
			ret = redirection_d_out(cmdNode->left->szData);
		if (ret == e_failure)
			return (e_failure);
		else
			cmdNode = cmdNode->right;
	}
	return (e_success);
}
