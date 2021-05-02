/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymori <ymori@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 23:33:36 by ymori             #+#    #+#             */
/*   Updated: 2021/05/02 13:40:13 by ymori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*re_tmp_push(char *tmp, long d)
{
	int		neg;
	int		i;

	neg = 0;
	if (d < 0)
		neg = 1;
	if (neg)
		d *= -1;
	i = 0;
	if (d == 0)
		tmp[i++] = '0';
	while (d)
	{
		tmp[i++] = '0' + d % 10;
		d /= 10;
	}
	if (neg)
		tmp[i++] = '-';
	tmp[i] = '\0';
	return (tmp);
}

char	*ft_itoa(int n)
{
	long	d;
	char	*p;
	char	tmp[12];
	size_t	tmp_len;
	size_t	i;

	d = (long)n;
	re_tmp_push(tmp, d);
	tmp_len = ft_strlen(tmp);
	p = (char *)malloc((tmp_len + 1) * sizeof(char));
	if (p == NULL)
		return (NULL);
	i = 0;
	while (tmp_len-- > 0)
		p[i++] = tmp[tmp_len];
	p[i] = '\0';
	return (p);
}
