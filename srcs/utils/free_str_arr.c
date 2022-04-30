/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_str_arr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymori <ymori@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 14:40:46 by ymori             #+#    #+#             */
/*   Updated: 2022/04/30 14:40:49 by ymori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


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
