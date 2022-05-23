#include "parser.h"

/**
 *
 * @param curtok
 * @return
 *
 * < >
 * ::=	'<' <token>
 */
t_astree	*REDIRECTION1(t_token_list **curtok)
{
	t_astree	*result;
	char		*filename;

	if (!term(CHAR_LESSER, NULL, curtok))
		return (NULL);
	if (!term(TOKEN, &filename, curtok))
		return (NULL);
	result = malloc(sizeof(*result));
	parse_malloc_errordeal(result, NULL);
	astreeset_type(result, NODE_REDIRECT_IN | NODE_DATA);
	astreeset_data(result, filename);
	astree_attach(result, NULL, NULL);
	return (result);
}

/**
 *
 * @param curtok
 * @return
 *
 * < >
 * ::=	'>' <token>
 */
t_astree	*REDIRECTION2(t_token_list **curtok)
{
	t_astree	*result;
	char		*filename;

	if (!term(CHAR_GREATER, NULL, curtok))
		return (NULL);
	if (!term(TOKEN, &filename, curtok))
		return (NULL);
	result = malloc(sizeof(*result));
	parse_malloc_errordeal(result, NULL);
	astreeset_type(result, NODE_REDIRECT_OUT | NODE_DATA);
	astreeset_data(result, filename);
	astree_attach(result, NULL, NULL);
	return (result);
}

/**
 *
 * @param curtok
 * @return
 *
 * < >
 * ::=	'<<' <token>
 */
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
	astreeset_type(result, NODE_REDIRECT_D_IN | NODE_DATA);
	astreeset_data(result, filename);
	astree_attach(result, NULL, NULL);
	return (result);
}

/**
 *
 * @param curtok
 * @return
 *
 * < >
 * ::=	'>>' <token>
 */
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
	astreeset_type(result, NODE_REDIRECT_D_OUT | NODE_DATA);
	astreeset_data(result, filename);
	astree_attach(result, NULL, NULL);
	return (result);
}
