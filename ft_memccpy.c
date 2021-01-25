/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymori <ymori@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 15:10:22 by ymori             #+#    #+#             */
/*   Updated: 2021/01/25 16:16:25 by ymori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *d, const void *s, int c, size_t n)
{
	unsigned char			*dst;
	const unsigned char		*src;
	unsigned char			ch;

	dst = (unsigned char *)d;
	src = (const unsigned char *)s;
	ch = (unsigned char)c;
	while (n-- > 0)
	{
		*dst++ = *src;
		if (*src++ == ch)
			return (dst);
	}
	return (NULL);
}