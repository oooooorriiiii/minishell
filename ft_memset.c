/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymori <ymori@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 16:25:06 by ymori             #+#    #+#             */
/*   Updated: 2021/01/20 20:10:26 by ymori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdio.h>
#include <unistd.h>

void	*ft_memset(void *b, int c, size_t len)
{
	const unsigned char uc = c;
	unsigned char		*p;

	p = (unsigned char *)b;
	while (len-- > 0)
	{
		*p++ = uc;
	}
	return (b);
}
