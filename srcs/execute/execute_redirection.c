#include "execute.h"

void	redirection_in(char *filename, t_cmd_args *args)
{
	int	fd;

	fd = open(filename, O_RDONLY);

	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	execute_redirection(t_astree *cmdNode, t_cmd_args *args)
{
	while (cmdNode && (cmdNode->type & NODE_REDIRECTION_LIST))
	{
		if (cmdNode->left->type & NODE_REDIRECT_IN)
		{
			redirection_in(cmdNode->left->szData);
			return ;
		}
		else if (cmdNode->left->type & NODE_REDIRECT_OUT)
		{

		}
	}
}
