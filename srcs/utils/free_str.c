//
// Created by ymori on 1/29/22.
//

#include <stdlib.h>

void	free_str(char **str)
{
	free(*str);
	*str = NULL;
}
