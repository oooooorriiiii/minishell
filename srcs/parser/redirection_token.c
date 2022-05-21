#include "parser.h"

/*
 * < >
 * ::=	'<' <token>
 */
t_astree	*RIDIRECTION1(t_token_list **curtok)
{
	t_astree	*result;
	char		*filename;

	result = malloc(sizeof(*result));
	parse_malloc_errordeal(result, NULL);
	astreeset_type(result, NODE_REDIRECT_IN);
	astreeset_data(result, filename);
	return (result);
}

/*
 * < >
 * ::=	'>' <token>
 */
t_astree	*RIDIRECTION2(t_token_list **curtok)
{
	t_astree	*result;
	char		*filename;

	if (!term(TOKEN, &filename, curtok))
		return (NULL);
	result = malloc(sizeof(*result));
	parse_malloc_errordeal(result, NULL);
	astreeset_type(result, NODE_REDIRECT_OUT);
	astreeset_data(result, filename);
	return (result);
}

/*
 * < >
 * ::=	'<<' <token>
 */
t_astree	*RIDIRECTION11(t_token_list **curtok)
{
	t_astree	*result;
	char		*filename;

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
t_astree	*RIDIRECTION22(t_token_list **curtok)
{
	t_astree	*result;
	char		*filename;

	if (!term(TOKEN, &filename, curtok))
		return (NULL);
	result = malloc(sizeof(*result));
	parse_malloc_errordeal(result, NULL);
	astreeset_type(result, NODE_REDIRECT_D_OUT);
	astreeset_data(result, filename);
	return (result);
}
