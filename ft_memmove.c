/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymori <ymori@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 00:08:31 by ymori             #+#    #+#             */
/*   Updated: 2021/01/24 02:54:48 by ymori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove (void *dst0, void const *src0, size_t length)
{
	char		*dst;
	char const	*src;

	dst = (char *)dst0;
	src = (const char *)src0;
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
	return (dst0);
}