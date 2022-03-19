/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_name_rule.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymori <ymori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 03:39:16 by ymori             #+#    #+#             */
/*   Updated: 2022/01/30 03:39:21 by ymori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_env.h"

/*
 * satisfy case
 * 	_ABC
 * 	ABC
 * 	A_3_2
 * error case
 * 	0AB
 * 	E+X
 */
bool	satisfy_env_name_rule(char *key)
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
