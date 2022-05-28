#include "execute.h"
#include "msh_signal.h"
#include <wait.h>
#include <errno.h>

pid_t	execute_pipe(t_astree *astree, t_cmd_args *args)
{
	int		file_desc[2];
	pid_t	pid;

	pipe(file_desc);
	pid = fork();
	if (pid == 0)
	{
		dup2(file_desc[STDOUT_FILENO], STDOUT_FILENO);
		close(file_desc[0]);
		close(file_desc[1]);
		execute_command(astree, args);
		exit(0);
	}
	dup2(file_desc[STDIN_FILENO], STDIN_FILENO);
	close(file_desc[0]);
	close(file_desc[1]);
	return (pid);
}

void
job_processer(t_astree *jobNode, t_cmd_args *args, pid_t *pid, int *status)
{
	if (jobNode->type & NODE_PIPE)
	{
		*pid = execute_pipe(jobNode->left, args);
		job_processer(jobNode->right, args, pid, status);
	}
	else
	{
		if (*pid == -1 && check_builtin_in_astree(jobNode))
			execute_command(jobNode, args);
		else
		{
			*pid = fork();
			if (*pid == 0)
			{
				execute_command(jobNode, args);
				exit(g_minishell.exit_status);
			}
		}
	}
}

/**
 *
 * @param jobNode
 * @param args
 *
 */
void	execute_job(t_astree *jobNode, t_cmd_args *args, int *status)
{
	pid_t	pid;
	pid_t	wait_pid;
	int		child_status;
	int		fd[2];

	wait_pid = 0;
	pid = -1;
	fd[0] = dup(STDIN_FILENO);
	fd[1] = dup(STDOUT_FILENO);
	signal_init(signal_child_process, signal_child_process, NULL);
	job_processer(jobNode, args, &pid, status);
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
//	if (jobNode == NULL)
//		return ;
//	if (jobNode->type == NODE_PIPE)
//		execute_pipeline(jobNode, args);
//	else if (jobNode->type == NODE_CMDPATH)
//		execute_command(jobNode, args);
//	else
//		execute_command(jobNode, args);
	while (wait_pid >= 0)
	{
		wait_pid = waitpid(-1, &child_status, 0);
		if (wait_pid != -1 && wait_pid == pid)
			*status = child_status;
	}
	if (errno != ECHILD)
	{
		perror("job error");
		exit(1);
	}
	errno = 0;
	signal_init(signal_handler_prompt, SIG_IGN, NULL);
}
