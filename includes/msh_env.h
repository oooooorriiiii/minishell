//
// Created by ymori on 1/28/22.
//

#ifndef MSH_ENV_H
# define MSH_ENV_H

# include <stdbool.h>

typedef struct s_envlist
{
	char			*key;
	char			*value;
	bool				is_shell_var;
	struct s_envlist	*next;
}	t_envlist;

t_envlist	*create_envlist(char **envp);
void	print_envlist(t_envlist *list);
void	envlist_clear(t_envlist **list);

#endif
