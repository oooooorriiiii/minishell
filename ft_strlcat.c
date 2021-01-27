/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymori <ymori@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 03:13:02 by ymori             #+#    #+#             */
/*   Updated: 2021/01/27 02:00:50 by ymori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *d, const char *s, size_t max_dstsize)
{
	char		*dst;
	const char	*src;
	size_t		dstlen;
	size_t		cnt_tmp;

	dst = d;
	src = s;
	cnt_tmp = max_dstsize;
	while (cnt_tmp-- > 0 && *dst != '\0')
		dst++;
	dstlen = dst - d;
	cnt_tmp = max_dstsize - dstlen;
	if (cnt_tmp == 0)
		return (dstlen + ft_strlen(src));
	while (*src != '\0')
	{
		if (cnt_tmp > 1)
		{
			*dst++ = *src;
			cnt_tmp--;
		}
		src++;
	}
	*dst = '\0';
	return (dstlen + (src - s));
}
