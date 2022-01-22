/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 19:23:52 by sosugimo          #+#    #+#             */
/*   Updated: 2022/01/22 19:46:21 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	execute_command_internal(t_cmd_args *args)
{
	if (args->cmdpath_argc < 0)
		return ;
	if (strcmp(args->cmdpath[0], "echo") == 0)
	{
		execute_echo(args);
		return ;
	}
	else if (strcmp(args->cmdpath[0], "cd") == 0)
	{
		execute_cd(args);
		return ;
	}
	else if (strcmp(args->cmdpath[0], "pwd") == 0)
		return (execute_pwd(args));
	else if (strcmp(args->cmdpath[0], "export") == 0)
	{
		execute_export(args);
		return ;
	}
	else if (strcmp(args->cmdpath[0], "unset") == 0)
	{
		execute_unset(args);
		return ;
	}
	else if (strcmp(args->cmdpath[0], "env") == 0)
	{
		execute_env(args);
		return ;
	}
	else if (strcmp(args->cmdpath[0], "exit") == 0)
	{
		exit(0);
		return ;
	}

	pid_t pid;
	if((pid = fork()) == 0 ) {
		// restore the signals in the child process
		restore_sigint_in_child();

		// store the stdout file desc
		int stdoutfd = dup(STDOUT_FILENO);

		// for bckgrnd jobs redirect stdin from /dev/null
		/*
		if (cmdinternal->asynchrnous) {
			int fd = open("/dev/null",O_RDWR);
			if (fd == -1) {
				perror("/dev/null");
				exit(1);
			}
			dup2(fd, STDIN_FILENO);
		}
		*/

		// redirect stdin from file if specified
		if (cmdinternal->redirect_in) {
			int fd = open(cmdinternal->redirect_in, O_RDONLY);
			if (fd == -1) {
				perror(cmdinternal->redirect_in);
				exit(1);
			}

			dup2(fd, STDIN_FILENO);
		}

		// redirect stdout to file if specified
		else if (cmdinternal->redirect_out) {
			int fd = open(cmdinternal->redirect_out, O_WRONLY | O_CREAT | O_TRUNC,
						  S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
			if (fd == -1) {
				perror(cmdinternal->redirect_out);
				exit(1);
			}

			dup2(fd, STDOUT_FILENO);
		}

		// read stdin from pipe if present
		// stdin用のfdに割り当て
		if (cmdinternal->stdin_pipe)
			dup2(cmdinternal->pipe_read, STDIN_FILENO);

		// write stdout to pipe if present
		// stdout用のfdに割り当て
		if (cmdinternal->stdout_pipe)
			dup2(cmdinternal->pipe_write, STDOUT_FILENO);

		if (execvp(cmdinternal->argv[0], cmdinternal->argv) == -1) {
			// restore the stdout for displaying error message
			dup2(stdoutfd, STDOUT_FILENO);

			printf("Command not found: \'%s\'\n", cmdinternal->argv[0]);
			exit(1);
		}


	}
	else if (pid < 0) {
		perror("fork");
		return;
	}

	if (!cmdinternal->asynchrnous)
	{
		// wait till the process has not finished
		while (waitpid(pid, NULL, 0) <= 0);
	}
	else
	{
		// set the sigchild handler for the spawned process
		printf("%d started\n", pid);
		struct sigaction act;
		act.sa_flags = 0;
		act.sa_handler = zombie_process_handler;
		sigfillset( & (act.sa_mask) ); // to block all

		if (sigaction(SIGCHLD, &act, NULL) != 0)
			perror("sigaction");
	}

	return;
}

int	init_command_internal(t_astree *simplecmdNode, t_cmd_args *args)
{
	t_astree	*argNode;
	int			i;

	i = 0;
	if (simplecmdNode == NULL || simplecmdNode->type != NODE_CMDPATH)
	{
		cmdinternal->argc = 0;
		return (-1);
	}
	argNode = simplecmdNode;
	while (argNode != NULL && argNode->type == NODE_ARGUMENT
		|| argNode->type == NODE_CMDPATH)
	{
		argNode = argNode->right;
		i++;
	}
	args->cmdpath = (char **)malloc(sizeof(char *) * (i + 1));
	argNode = simplecmdNode;
	i = 0;
	while (argNode != NULL && argNode->type == NODE_ARGUMENT
		|| argNode->type == NODE_CMDPATH)
	{
		args->cmdpath[i] = (char *)malloc(strlen(argNode->szData) + 1);
		strcpy(args->cmdpath[i], argNode->szData);
		argNode = argNode->right;
		i++;
	}
	args->cmdpath[i] = NULL;
	args->cmdpath_argc = i;
	return (0);
}
