#include "../includes/parser.h"

/*
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

/*
 * REDIRECTION_LIST
 * <redirection_list> ::= <redirection>
 *                      | <recirection> <redirection_list>
 */
t_astree	*REDIRECTION_LIST(t_token_list **curtok)
{
//	t_astree	*result;
//
//	result = REDIRECTION(curtok);
//	if (result == NULL)
//		return (NULL);
//	result = REDIRECTION(curtok);
//	return (result);
	return (REDIRECTION(curtok));
}
