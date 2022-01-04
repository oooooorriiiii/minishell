#include "minishell.h"

bool	is_quote(char c)
{
	if (c == SINGLE_QUOTE || c == DOUBLE_QUOTE)
		return (true);
	return (false);
}
