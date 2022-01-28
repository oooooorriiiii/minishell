#include "msh_env.h"
#include "msh_error.h"
#include "../../libft/libft.h"
#include <stdlib.h>
#include <stdbool.h>

#include <stdio.h>

void	print_envlist(t_envlist *list)
{
	puts("------env list------");
	if (list == NULL)
	{
		printf("NULL\n");
		return ;
	}
	while (list->next)
	{
		printf("key     : %s\n", list->key);
		printf("value   : %s\n", list->value);
		printf("is_shell: %d\n", list->is_shell_var);
		list = list->next;
	}
	printf("key     : %s\n", list->key);
	printf("value   : %s\n", list->value);
	printf("is_shell: %d\n", list->is_shell_var);
}

void	envlist_delone(t_envlist *list)
{
	if (list == NULL)
		return ;
	free(list->key);
	free(list->value);
	free(list);
}

void	envlist_clear(t_envlist **list)
{
	t_envlist	*list_tmp;
	t_envlist	*next_tmp;

	list_tmp = *list;
	while (list_tmp)
	{
		next_tmp = list_tmp->next;
		envlist_delone(list_tmp);
		list_tmp = next_tmp;
	}
	*list = NULL;
}

static void			set_elements(char *env, t_envlist *new)
{
	char 	*key;
	char 	*value;
	char 	*p_equal;
	size_t	key_len;

	p_equal = ft_strchr(env, '=');
	key_len = p_equal - env;
	key = ft_substr(env, 0, key_len);
	value = ft_substr(env, key_len + 1, ft_strlen(env) - key_len - 1);
	new->key = key;
	new->value = value;
	new->is_shell_var = true;
}

static t_envlist	*envlist_listnew(t_envlist *current, char *env)
{
	t_envlist	*new_env;

	new_env = malloc(sizeof(t_envlist));
	set_elements(env, new_env);
	current->next = new_env;
	return (new_env);
}

t_envlist	*create_envlist(char **envp)
{
	t_envlist	head;
	t_envlist	*current;
	size_t		i;

	i = 0;
	current = &head;
	if (envp[i] == NULL)
		return (NULL);
	while (envp[i])
	{
		current = envlist_listnew(current, envp[i]);
		i++;
	}
	current->next = NULL;
	return (head.next);
}
