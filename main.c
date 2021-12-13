#include <unistd.h>

int	main(void)
{
	write(STDOUT_FILENO, "Hello, minishell\n", 18);
	return (0);
}