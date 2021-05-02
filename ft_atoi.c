/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymori <ymori@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 14:46:07 by ymori             #+#    #+#             */
/*   Updated: 2021/05/02 13:49:14 by ymori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	const char	*s;
	long		out;
	int			neg;

	s = nptr;
	out = 0;
	neg = 0;
	while (*s == '\t' || *s == '\n' || *s == '\v' || \
	*s == '\f' || *s == '\r' || *s == ' ')
		s++;
	if (*s == '-')
	{
		neg = 1;
		s++;
	}
	else if (*s == '+')
		s++;
	while ((*s >= '0' && *s <= '9') && *s != '\0')
	{
		out *= 10;
		out += *s++ - '0';
	}
	if (neg)
		return (-out);
	return (out);
}
