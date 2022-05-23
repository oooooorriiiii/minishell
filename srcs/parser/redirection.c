#include "../includes/parser.h"

 /**
  *
  * @param curtok
  * @return
  *
  * <redirection> ::= '>' <word>   ->REDIRECTION1
  *                 | '<' <word>   ->REDIRECTION2
  *                 | '>>' <word>  ->REDIRECTION11
  *                 | '<<' <word>  ->REDIRECTION22
  */
t_astree	*REDIRECTION(t_token_list **curtok)
{
	t_token_list		*save;
	t_astree			*node;

	save = *curtok;
	*curtok = save;
	node = REDIRECTION1(curtok);
	if (node != NULL)
		return (node);
	*curtok = save;
	node = REDIRECTION2(curtok);
	if (node != NULL)
		return (node);
	*curtok = save;
	node = REDIRECTION11(curtok);
	if (node != NULL)
		return (node);
	*curtok = save;
	node = REDIRECTION22(curtok);
	if (node != NULL)
		return (node);
	return (NULL);
}

/**
 *
 * @param curtok
 * @return
 *
 * <redirection> <redirection list>
 */
t_astree	*REDIRECTION_LIST1(t_token_list **curtok)
{
	t_astree	*redirectionNode;
	t_astree	*redirectionListNode;
	t_astree	*result;

	redirectionNode = REDIRECTION(curtok);
	if (redirectionNode == NULL)
		return (NULL);
	redirectionListNode = REDIRECTION_LIST(curtok);
	result = malloc(sizeof(t_astree));
	parse_malloc_errordeal(result, NULL);
	astreeset_type(result, NODE_REDIRECTION_LIST);
	astreeset_data(result, NULL);
	astree_attach(result, redirectionNode, redirectionListNode);
	return (result);
}

/**
 *
 * @param curtok
 * @return
 *
 * <redirection list> ::= <redirection> <redirection list> -> REDIRECTION_LIST1
 */
t_astree	*REDIRECTION_LIST(t_token_list **curtok)
{
	return (REDIRECTION_LIST1(curtok));
}
