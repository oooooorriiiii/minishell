//
// Created by yuumo on 2022/05/10.
//

#include "libft.h"
#include "minishell.h"

char	*ft_xstrdup(const char *s1)
{
	char *str;

	str = ft_strdup(s1);
	if (str == NULL)
	{
		perror("ft_strdup");
		exit(1);
	}
	return (str);
}
