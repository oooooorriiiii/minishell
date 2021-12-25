#include <unistd.h>
#include "minishell.h"

int	main(void)
{
	write(STDOUT_FILENO, "Hello, minishell\n", 18);
	write(STDOUT_FILENO, "Hello, minishell\n", 18);
	ft_putstr_fd("Hello, libft\n", STDOUT_FILENO);
	write(STDOUT_FILENO, "Hello, minishell\n", 18);
	return (0);
}