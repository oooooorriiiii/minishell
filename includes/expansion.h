/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymori <ymori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 22:09:02 by ymori             #+#    #+#             */
/*   Updated: 2022/05/28 22:09:02 by ymori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include "parser.h"

// expansion.c
char	*expansion_env(char *content);

// expantion_general.c
char	*general_expansion(char *data);

// expansion_utils.c
char	*ft_strpbrk(const char *s1, const char *s2);
t_list	*split_to_list(char *line);
char	*list_to_str(t_list *list);

#endif
