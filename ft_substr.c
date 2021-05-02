/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymori <ymori@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 17:20:28 by ymori             #+#    #+#             */
/*   Updated: 2021/05/02 13:36:04 by ymori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*p;
	size_t	s_i;
	size_t	p_i;

	if (s == NULL)
		return (NULL);
	s_i = start;
	p_i = 0;
	p = (char *)malloc((len + 1) * sizeof(char));
	if (p == NULL)
		return (NULL);
	while (p_i < len && start <= ft_strlen(s))
		p[p_i++] = s[s_i++];
	p[p_i] = '\0';
	return (p);
}
