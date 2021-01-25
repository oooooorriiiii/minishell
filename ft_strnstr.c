/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymori <ymori@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 15:16:31 by ymori             #+#    #+#             */
/*   Updated: 2021/01/24 15:53:28 by ymori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t length)
{
	size_t	h_i;
	size_t	n_i;

	if (*needle == '\0')
		return ((char *)haystack);
	h_i = 0;
	while (haystack[h_i] != '\0')
	{
		n_i = 0;
		while (haystack[h_i + n_i] != '\0' && \
				haystack[h_i + n_i] == needle[n_i] && h_i + n_i < length)
		{
			if (needle[n_i + 1] == '\0')
				return ((char *)&haystack[h_i]);
			n_i++;
		}
		h_i++;
	}
	return (NULL);
}