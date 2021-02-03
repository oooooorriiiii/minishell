/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymori <ymori@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 00:08:31 by ymori             #+#    #+#             */
/*   Updated: 2021/02/03 21:28:17 by ymori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *d, void const *s, size_t length)
{
	char		*dst;
	char const	*src;

	dst = (char *)d;
	src = (const char *)s;
	if (src < dst)
	{
		src += length;
		dst += length;
		while (length-- > 0)
			*--dst = *--src;
	}
	else if (src != dst)
	{
		while (length-- > 0)
			*dst++ = *src++;
	}
	return (d);
}
