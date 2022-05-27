#include "parser.h"
#include "expansion.h"
#include "msh_error.h"

char	*ft_strpbrk(const char *s1, const char *s2)
{
	const char	*t = s2;

	while (*s1)
	{
		while (*t)
		{
			if (*t == *s1)
				return ((char *)s1);
			t++;
		}
		s1++;
	}
	return (NULL);
}

t_list	*split_to_list(char *line)
{
	const char	*sep_char = " \t\n\v\f\r\?\'\"$";
	t_list		*new_list;
	char		*head;

	new_list = NULL;
	while (*line != '\0')
	{
		if (ft_strchr(sep_char, *line) != NULL)
		{
			ft_lstadd_back(&new_list, ft_lstnew(ft_substr(line, 0, 1)));
			line++;
		}
		else
		{
			head = line;
			while (ft_strchr(sep_char, *line) == NULL)
				line++;
			ft_lstadd_back(&new_list, \
				ft_lstnew(ft_substr(head, 0, line - head)));
		}
	}
	return (new_list);
}

char	*list_to_str(t_list *list)
{
	char	*ret_str;

	if (list == NULL)
		msh_fatal("expansion");
	if ((char *)list->content != NULL)
		ret_str = ft_strdup((char *)list->content);
	else
		ret_str = ft_strdup("");
	while (list->next)
	{
		free_set((void **)&ret_str, ft_strjoin(ret_str, ""));
		if ((char *)list->next->content != NULL)
			free_set((void **)&ret_str, \
			ft_strjoin(ret_str, (char *)list->next->content));
		list = list->next;
	}
	return (ret_str);
}
