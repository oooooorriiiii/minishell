//
// Created by ymori on 1/28/22.
//

#include <stdlib.h>

void 	free_str_arr(char ***str)
{
	size_t	i;

	i = 0;
	if (!(*str))
		return ;
	while ((*str)[i])
	{
		free((*str)[i]);
		(*str)[i] = NULL;
		i++;
	}
	free(*str);
	*str = NULL;
}

