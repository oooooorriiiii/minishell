/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_general.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymori <ymori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 22:08:19 by ymori             #+#    #+#             */
/*   Updated: 2022/05/28 22:08:19 by ymori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "expansion.h"
#include "msh_error.h"

void	expansion_dollar_general(char *content, t_status status, t_list *list)
{
	if (ft_strcmp(content, "$") == 0 \
		&& status != STATUS_QUOTE \
		&& list->next != NULL \
		&& ft_strpbrk((const char *)list->next->content, " \t\n\v\f\r\"\'") \
			== NULL)
	{
		free_set(&list->content, NULL);
		list = list->next;
		free_set(&list->content, expansion_env((char *)list->content));
	}
}

void	expansion_quotes_dollar(char *content, t_status *status, t_list *list)
{
	if (ft_strcmp(content, "\'") == 0 && *status == STATUS_GENERAL)
	{
		free_set(&list->content, NULL);
		*status = STATUS_QUOTE;
	}
	else if (ft_strcmp(content, "\'") == 0 && *status == STATUS_QUOTE)
	{
		free_set(&list->content, NULL);
		*status = STATUS_GENERAL;
	}
	else if (ft_strcmp(content, "\"") == 0 && *status == STATUS_GENERAL)
	{
		free_set(&list->content, NULL);
		*status = STATUS_DQUOTE;
	}
	else if (ft_strcmp(content, "\"") == 0 && *status == STATUS_DQUOTE)
	{
		free_set(&list->content, NULL);
		*status = STATUS_GENERAL;
	}
	else
	{
		expansion_dollar_general(content, *status, list);
	}
}

//printf("before: expansion---\n"); // D
//list_print(sep_data); // D
//printf("before: expansion---\n"); // D
//printf("after: expansion---\n"); // D
//list_print(sep_data); // D
//printf("after: expansion---\n"); // D
char	*general_expansion(char *data)
{
	t_list		*sep_data;
	t_list		*head;
	char		*ret;
	char		*content;
	t_status	status;

	status = STATUS_GENERAL;
	if (data == NULL)
		msh_fatal("expamsion");
	if (*data == '\0')
		return (ft_strdup(data));
	sep_data = split_to_list(data);
	head = sep_data;
	while (sep_data)
	{
		content = (char *)sep_data->content;
		expansion_quotes_dollar(content, &status, sep_data);
		sep_data = sep_data->next;
	}
	sep_data = head;
	ret = list_to_str(sep_data);
	ft_lstclear(&sep_data, free);
	return (ret);
}
