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

	redirectionNode = REDIRECTION(curtok);
	if (redirectionNode == NULL)
		return (NULL);
	return (REDIRECTION_LIST(curtok));
}

/**
 *
 * @param curtok
 * @return
 *
 * <redirection>
 */
t_astree	*REDIRECTION_LIST2(t_token_list **curtok)
{
	return (REDIRECTION(curtok));
}

/**
 *
 * @param curtok
 * @return
 *
 * <EMPTY>
 */
t_astree	*REDIRECTION_LIST3(t_token_list **curtok)
{
	(void)curtok;
	return (NULL);
}

/**
 *
 * @param curtok
 * @return
 *
 * <redirection list> ::= <redirection> <redirection list> -> REDIRECTION_LIST1
 *                      | <redirection>                    -> REDIRECTION_LIST2
 *                      | <EMPTY>                          -> REDIRECTION_LIST3
 */
t_astree	*REDIRECTION_LIST(t_token_list **curtok)
{
	t_token_list	*save;
	t_astree		*node;

	save = *curtok;
	*curtok = save;
	node = REDIRECTION_LIST1(curtok);
	if (node != NULL)
		return (node);
	*curtok = save;
	node = REDIRECTION_LIST2(curtok);
	if (node != NULL)
		return (node);
	return (REDIRECTION_LIST3(curtok));
}
