#include "../includes/parser.h"

/*
 * <redirection> ::= '>' <word>   ->RIDIRECTION1
 *                 | '<' <word>   ->RIDIRECTION2
 *                 | '>>' <word>  ->RIDIRECTION11
 *                 | '<<' <word>  ->RIDIRECTION22
 */
t_astree	*REDIRECTION(t_token_list **curtok)
{
	t_astree	*result;

	if ((*curtok)->type == CHAR_LESSER)
		result = RIDIRECTION1(curtok);
	else if ((*curtok)->type == CHAR_GREATER)
		result = RIDIRECTION2(curtok);
	else if ((*curtok)->type == CHAR_DBLLESSER)
		result = RIDIRECTION11(curtok);
	else if ((*curtok)->type == CHAR_DBLGREATER)
		result = RIDIRECTION22(curtok);
	else
		result = NULL;
	return (result);
}

/*
 * RIDIRECTION_LIST
 * <redirection_list> ::= <redirection>
 *                      | <recirection> <redirection_list>
 */
t_astree	*RIDIRECTION_LIST(t_token_list **curtok)
{
	t_astree	*result;

	result = REDIRECTION(curtok);
	if (result == NULL)
		return (NULL);
	result = REDIRECTION(curtok);
	return (result);
}
