<<<<<<< HEAD
//
// Created by ymori on 1/29/22.
//

#include <stdlib.h>

void	free_str(char **str)
{
	free(*str);
	*str = NULL;
}
=======
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymori <ymori@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 14:40:21 by ymori             #+#    #+#             */
/*   Updated: 2022/04/30 14:40:26 by ymori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	free_str(char **str)
{
	free(*str);
	*str = NULL;
}
>>>>>>> ba2b558f9fb4576505b8cd43038ee974a9f361a7
