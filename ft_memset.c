/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymori <ymori@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 16:25:06 by ymori             #+#    #+#             */
/*   Updated: 2021/02/03 21:07:08 by ymori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	uc;
	unsigned char	*p;

	uc = (unsigned char)c;
	p = (unsigned char *)b;
	while (len-- > 0)
		*p++ = uc;
	return (b);
}
