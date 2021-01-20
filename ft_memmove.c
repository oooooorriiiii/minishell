/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymori <ymori@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 00:08:31 by ymori             #+#    #+#             */
/*   Updated: 2021/01/20 00:16:17 by ymori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	*ft_memmove(void *dst0, const void *src0, size_t n)
{
	char		*dst;
	const char	*src;

	dst = (char *)dst0;
	src = (const char *)src0;
	if (dst < src && dst < src + n)
	{
		dst += n;
		while (n > 0)
		{
			*dst-- = *src--;
			n--;
		}
	}
	else
	{
		while (n > 0)
		{
			*dst = *src;
		}
	}
	return (dst0);
}
