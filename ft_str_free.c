#include "libft.h"

void	str_free(char **p)
{
	if (p != NULL && *p != NULL)
	{
		free(*p);
		*p = NULL;
	}
}
