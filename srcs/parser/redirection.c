#include "../includes/parser.h"

/*
 * <redirection> ::= '>' <word>  ->RIDIRECTION1
 *                | '<' <word>  ->RIDIRECTION2
 *                | '>>' <word>  ->RIDIRECTION11
 *                | '<<' <word>  ->RIDIRECTION22
 */
// TODO: ここおねがいします
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
// TODO: ここおねがいします
//t_astree	*RIDIRECTION_LIST(t_astree **curtok)
//{
//	REDIRECTION();
//	if ( == NULL)
//		return ;
//	RIDIRECTION(); // くりかえせるようにする
//}
