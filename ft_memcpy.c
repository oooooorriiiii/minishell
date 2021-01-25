/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymori <ymori@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 23:05:32 by ymori             #+#    #+#             */
/*   Updated: 2021/01/25 16:33:30 by ymori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *d, const void *s, size_t length)
{
	unsigned char		*dst;
	const unsigned char	*src;

	dst = (unsigned char *)d;
	src = (const unsigned char *)s;
	if (length == 0 || d == s)
		return (d);
	while (length-- > 0)
		*dst++ = *src++;
	return (d);
}
