//
// Created by ymori on 1/30/22.
//

#include "msh_env.h"

bool	satisfy_env_name_rule(*key)
{
	size_t	i;

	i = 0;
	if (key[i] != '_' && !ft_isalpha(key[i]))
		return (false);
	i++;
	while (key[i])
	{
		if (key[i] != '_' && !ft_isalnum(key[i]))
			return (false);
		i++;
	}
	return (true);
}
