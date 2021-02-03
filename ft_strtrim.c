/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymori <ymori@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 19:57:38 by ymori             #+#    #+#             */
/*   Updated: 2021/02/03 21:23:52 by ymori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_element(char c, const char *set)
{
	while (*set != '\0')
	{
		if (*set++ == c)
			return (1);
	}
	return (0);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	char	*p;
	size_t	head_i;
	size_t	tail_i;
	size_t	p_i;
	size_t	p_len;

	if (s1 == NULL || set == NULL)
		return (NULL);
	head_i = 0;
	tail_i = ft_strlen(s1);
	p_i = 0;
	while (is_element(s1[head_i], set))
		head_i++;
	while (is_element(s1[tail_i - 1], set) && head_i < tail_i)
		tail_i--;
	p_len = tail_i - head_i;
	p = (char *)malloc((p_len + 1) * sizeof(char));
	if (p == NULL)
		return (NULL);
	while (p_i < p_len)
		p[p_i++] = s1[head_i++];
	p[p_i] = '\0';
	return (p);
}
