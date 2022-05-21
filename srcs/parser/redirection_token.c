#include "parser.h"

/*
 * < >
 * ::=	'<' <token>
 */
// TODO:
t_astree	*REDIRECTION1(t_token_list **curtok)
{
	t_astree	*result;
	t_astree	*simpleCmdNode;
	t_astree	*redirectNode;
//	char		*filename;

	simpleCmdNode = SIMPLECMD1(curtok);
	if (simpleCmdNode == NULL)
		return (NULL);
	if (!term(CHAR_LESSER, NULL, curtok))
	{
		astree_delete(simpleCmdNode);
		return (NULL);
	}
//	if (!term(TOKEN, &filename, curtok))
//	{
//		astree_delete(simpleCmdNode);
//		return (NULL);
//	}
	redirectNode = REDIRECTION_LIST(curtok);
	if (redirectNode == NULL)
	{
		astree_delete(simpleCmdNode);
		return (NULL);
	}
	result = malloc(sizeof(*result));
	parse_malloc_errordeal(result, NULL);
	astreeset_type(result, NODE_REDIRECT_IN);
	astree_attach(result, simpleCmdNode, redirectNode);
	return (result);
}

/*
 * < >
 * ::=	'>' <token>
 */
t_astree	*REDIRECTION2(t_token_list **curtok)
{
	t_astree	*result;
	t_astree	*simpleCmdNode;
	t_astree	*redirectNode;
//	char		*filename;

	simpleCmdNode = SIMPLECMD1(curtok);
	if (simpleCmdNode == NULL)
		return (NULL);
	if (!term(CHAR_GREATER, NULL, curtok))
	{
		astree_delete(simpleCmdNode);
		return (NULL);
	}
	printf("redirection 2: "); // D
	print_token_list(*curtok); // D
//	if (!term(TOKEN, &filename, curtok))
//	{
//		astree_delete(simpleCmdNode);
//		return (NULL);
//	}
	redirectNode = TOKENLIST(curtok); // TODO:
	printf("redirect------------------------\n"); // D
	print_syntax_tree(redirectNode); // D
	printf("********------------------------\n"); // D
	if (redirectNode == NULL)
	{
		astree_delete(simpleCmdNode);
		return (NULL);
	}
	printf("ok\n"); // D
	print_token_list(*curtok); // D
	result = malloc(sizeof(*result));
	parse_malloc_errordeal(result, NULL);
	astreeset_type(result, NODE_REDIRECT_OUT);
	astree_attach(result, simpleCmdNode, redirectNode);
	return (result);
}

/*
 * < >
 * ::=	'<<' <token>
 */
// TODO:
t_astree	*REDIRECTION11(t_token_list **curtok)
{
	t_astree	*result;
	char		*filename;

	if (!term(CHAR_DBLLESSER, NULL, curtok))
		return (NULL);
	if (!term(TOKEN, &filename, curtok))
		return (NULL);
	result = malloc(sizeof(*result));
	parse_malloc_errordeal(result, NULL);
	astreeset_type(result, NODE_REDIRECT_D_IN);
	astreeset_data(result, filename);
	return (result);
}

/*
 * < >
 * ::=	'>>' <token>
 */
// TODO:
t_astree	*REDIRECTION22(t_token_list **curtok)
{
	t_astree	*result;
	char		*filename;

	if (!term(CHAR_DBLGREATER, NULL, curtok))
		return (NULL);
	if (!term(TOKEN, &filename, curtok))
		return (NULL);
	result = malloc(sizeof(*result));
	parse_malloc_errordeal(result, NULL);
	astreeset_type(result, NODE_REDIRECT_D_OUT);
	astreeset_data(result, filename);
	return (result);
}
