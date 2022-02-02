/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astree.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 00:20:19 by sosugimo          #+#    #+#             */
/*   Updated: 2022/02/03 00:36:46 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

void	astree_attach(t_astree *root, t_astree *leftNode, t_astree *rightNode)
{
	// assert(root != NULL);
	root->left = leftNode;
	root->right = rightNode;
}

void	astreeset_type(t_astree	*node, t_node_type nodetype)
{
	// assert(node != NULL);
	node->type = nodetype;
}

void	astreeset_data(t_astree *node, char *data)
{
	// assert(node != NULL);
	if (data != NULL)
	{
		node->szData = data;
		// node->type |= NODE_DATA;
	}
}

void	astree_delete(t_astree *node)
{
	if (node == NULL)
		return ;
	if (node->type >= NODE_REDIRECT_IN)
	{
		// printf("node->type  :    %d\n", node->type);
		free(node->szData);
	}
	astree_delete(node->left);
	astree_delete(node->right);
	free(node);
	return ;
}
