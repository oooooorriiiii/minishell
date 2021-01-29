/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymori <ymori@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 21:41:17 by ymori             #+#    #+#             */
/*   Updated: 2021/01/29 00:48:34 by ymori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*p;
	size_t	p_i;

	if (s == NULL)
		return (NULL);
	p_i = 0;
	p = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (p == NULL)
		return (NULL);
	while (s[p_i] != '\0')
	{
		p[p_i] = f((unsigned int)p_i, s[p_i]);
		p_i++;
	}
	p[p_i] = '\0';
	return (p);
}
