/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymori <ymori@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 14:17:44 by ymori             #+#    #+#             */
/*   Updated: 2021/01/20 00:59:16 by ymori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const char	*str;
	int			ch;

	str = (const char *)s;
	ch = c;
	while (n-- > 0)
	{
		if (*str == ch)
		{
			return (str);
			str++;
		}
	}
	return (s);
}
