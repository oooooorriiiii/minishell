//
// Created by ymori on 2/2/22.
//

#include "execute.h"
#include "utils.h"

static char	**allocate_mem(const char *str)
{
	size_t	i;
	size_t	split_count;
	char	**ret_str_arr_ptr;

	i = 0;
	split_count = 0;
	while (str[i])
	{
		if (str[i] == ':')
			split_count++;
		i++;
	}
	ret_str_arr_ptr = malloc(sizeof(char *) * (split_count + 2));
	ret_str_arr_ptr[split_count + 1] = NULL;
	return (ret_str_arr_ptr);
}

static char	*strdup_elem(char *elem)
{
	char	*ret_str;

	if (!elem)
		return (NULL);
	if (ft_strlen(elem) == 0)
		ret_str = ft_strdup(".");
	else
		ret_str = ft_strdup(elem);
	return (ret_str);
}

char	**get_path_elem_in_envlist(const char *str)
{
	char	**ret_str_arr;
	char	*tmp_str;
	char	*elem_head;
	char	*elem_tail;
	size_t	i;

	i = 0;
	ret_str_arr = allocate_mem(str);
	tmp_str = ft_strdup(str);
	elem_head = tmp_str;
	elem_tail = ft_strchr(elem_head, ':');
	while (elem_tail)
	{
		*elem_tail = '\0';
		ret_str_arr[i] = strdup_elem(elem_head);
		elem_head = elem_tail + 1;
		elem_tail = ft_strchr(elem_head, ':');
		i++;
	}
	ret_str_arr[i] = strdup_elem(elem_head);
	free_str(&tmp_str);
	return (ret_str_arr);
}
