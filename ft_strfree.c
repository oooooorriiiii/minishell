#include "libft.h"

void	ft_strfree(char **p)
{
	if (p != NULL && *p != NULL)
	{
		free(*p);
		*p = NULL;
	}
}
