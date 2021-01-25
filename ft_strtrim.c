/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymori <ymori@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 19:57:38 by ymori             #+#    #+#             */
/*   Updated: 2021/01/25 21:20:12 by ymori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*p;
	int		set_i;
	int		str_i;

	set_i = 0;
	str_i = 0;
	p = (char *)malloc(strlen(s1) + 1);
	if (p == NULL)
		return (NULL);
}