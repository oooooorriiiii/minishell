/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymori <ymori@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 19:41:25 by ymori             #+#    #+#             */
/*   Updated: 2021/01/27 17:50:30 by ymori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*p;
	size_t	s_i;
	size_t	p_i;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	p_i = 0;
	s_i = 0;
	p = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (p == NULL)
		return (NULL);
	while (s1[s_i] != '\0')
		p[p_i++] = s1[s_i++];
	s_i = 0;
	while (s2[s_i] != '\0')
		p[p_i++] = s2[s_i++];
	p[p_i] = '\0';
	return (p);
}
