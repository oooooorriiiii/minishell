/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymori <ymori@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 23:33:36 by ymori             #+#    #+#             */
/*   Updated: 2021/01/26 03:52:29 by ymori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	long	d;
	char	*p;
	char	tmp[12];
	int		neg;
	size_t	tmp_len;
	size_t	i;

	d = (long)n;
	neg = 0;
	if (d < 0) neg = 1;
	if (neg) d *= -1;
	i = 0;
	if (d == 0) tmp[i++] = '0';
	while (d)
	{
		tmp[i++] = '0' + d % 10;
		d /= 10;
	}
	tmp[i] = '\0';
	tmp_len = ft_strlen(tmp);
	p = (char *)malloc(tmp_len + 1);
	if (p == NULL) return (NULL);
	i = 0;
	if (neg) p[i++] = '-';
	while (tmp_len-- > 0) p[i++] = tmp[tmp_len];
	p[i] = '\0';
	return (p);
}