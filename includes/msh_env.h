/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymori <ymori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 03:40:32 by ymori             #+#    #+#             */
/*   Updated: 2022/01/30 03:40:36 by ymori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_ENV_H
# define MSH_ENV_H

# include <stdlib.h>
# include <stdbool.h>
# include <stdbool.h>
# include "../libft/libft.h"

typedef struct s_envlist
{
	char				*key;
	char				*value;
	bool				is_shell_var;
	struct s_envlist	*next;
}	t_envlist;

t_envlist	*create_envlist(char **envp);
t_envlist	*envlist_listnew(t_envlist *current, char *env);
void		print_envlist(t_envlist *list);
void		envlist_clear(t_envlist **list);
char		**gen_env_str(t_envlist *envlist);

// ---env_list_utils.c
t_envlist	*msh_get_envlist(const char *key);
t_envlist	*envlist_listlast(t_envlist *envlist);
void		envlist_add_back(t_envlist **p_envlist, t_envlist *new_envlist);
void		envlist_del(t_envlist **p_envlist, char *key);

// env_name_rule.c
bool		satisfy_env_name_rule(char *key);

// update_env_val.c
void		update_env_val(const char *env_key, const char *new_env_val, \
							bool is_env_var, bool append_flag);

// get_env_value.c;
char		*get_env_value(const char *key);

#endif
