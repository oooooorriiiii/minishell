/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xstrdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymori <ymori@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 22:43:32 by ymori             #+#    #+#             */
/*   Updated: 2022/05/14 22:43:54 by ymori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

char	*ft_xstrdup(const char *s1)
{
	char	*str;

	str = ft_strdup(s1);
	if (str == NULL)
	{
		perror("ft_strdup");
		exit(1);
	}
	return (str);
}
