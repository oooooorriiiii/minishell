/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymori <ymori@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 23:05:32 by ymori             #+#    #+#             */
/*   Updated: 2021/01/20 00:21:33 by ymori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	*ft_memcpy(void *dst0, const void *src0, size_t n)
{
	char		*dst;
	const char	*src;

	dst = (char *)dst0;
	src = (const char *)src0;
	while (n-- > 0)
	{
		*dst = *src;
		dst++;
		src++;
	}
	return (dst0);
}
