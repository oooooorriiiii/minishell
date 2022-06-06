/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astree.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 00:20:19 by sosugimo          #+#    #+#             */
/*   Updated: 2022/02/05 17:57:10 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

void	astree_attach(t_astree *root, t_astree *leftNode, t_astree *rightNode)
{
	root->left = leftNode;
	root->right = rightNode;
}

void	astreeset_type(t_astree	*node, t_node_type nodetype)
{
	node->type = nodetype;
}

void	astreeset_data(t_astree *node, char *data)
{
	if (data != NULL)
		node->szData = data;
}

void	astree_delete(t_astree *node)
{
	if (node == NULL)
		return ;
	if (node->type >= NODE_REDIRECT_IN)
		free(node->szData);
	astree_delete(node->left);
	astree_delete(node->right);
	free(node);
	return ;
}

t_astree	*astree_right_node_last(t_astree *node)
{
	while (node->right != NULL)
		node = node->right;
	return (node);
}
