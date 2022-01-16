#include "parser.h"

tok_t* curtok = NULL;

bool term(int toketype, char** bufferptr)
{
	if (curtok == NULL)
		return false;

	if (curtok->type == toketype)
	{
		if (bufferptr != NULL)
		{
			*bufferptr = malloc(strlen(curtok->data) + 1);
			strcpy(*bufferptr, curtok->data);
		}
		curtok = curtok->next;
		return true;
	}
	curtok = curtok->next;
	return false;
}

t_astree* CMDLINE()
{
	return JOB();
}

t_astree* JOB()
{
	tok_t		*save;
	t_astree	*node;

	save = curtok
	curtok = save;
	node = JOB1();
	if (node != NULL)
		return node;
	curtok = save;
	node = JOB2();
	if (node != NULL)
		return node;
	return NULL;
}

t_astree* JOB1()
{
	t_astree* cmdNode;
	t_astree* jobNode;
	t_astree* result;

	cmdNode = CMD();
	if (cmdNode == NULL)
		return NULL;
	if (!term(CHAR_PIPE, NULL))
	{
		astree_delete(cmdNode);
		return NULL;
	}
	jobNode = JOB();
	if (jobNode== NULL)
	{
		astree_delete(cmdNode);
		return NULL;
	}
	result = malloc(sizeof(*result));
	dastreeset_type(result, NODE_PIPE);
	astree_attach(result, cmdNode, jobNode);
	return result;
}

t_astree* JOB2()
{
	return CMD();
}

t_astree* CMD()
{
	tok_t* save = curtok;

	t_astree* node;

	curtok = save;
	node = CMD1();
	if (node != NULL)
		return node;
	curtok = save;
	node = CMD2();
	if (node != NULL)
		return node;
	curtok = save;
	node = CMD3();
	if (node != NULL)
		return node;
	return NULL;
}

t_astree* CMD1()
{
	t_astree	*simplecmdNode;
	t_astree	*result;
	char		*filename;

	simplecmdNode = SIMPLECMD();
	if (simplecmdNode == NULL)
		return NULL;
	if (!term(CHAR_LESSER, NULL))
	{
		astree_delete(simplecmdNode);
		return NULL;
	}
	if (!term(TOKEN, &filename))
	{
		free(filename);
		astree_delete(simplecmdNode);
		return NULL;
	}
	result = malloc(sizeof(*result));
	dastreeset_type(result, NODE_REDIRECT_IN);
	astreeset_data(result, filename);
	astree_attach(result, NULL, simplecmdNode);
	return result;
}

t_astree* CMD2()
{
	t_astree	*simplecmdNode;
	t_astree	*result;
	char*		filename;

	simplecmdNode = SIMPLECMD();
	if (simplecmdNode == NULL)
		return NULL;
	if (!term(CHAR_GREATER, NULL))
	{
		astree_delete(simplecmdNode);
		return NULL;
	}
	if (!term(TOKEN, &filename))
	{
		free(filename);
		astree_delete(simplecmdNode);
		return NULL;
	}
	result = malloc(sizeof(*result));
	dastreeset_type(result, NODE_REDIRECT_OUT);
	astreeset_data(result, filename);
	astree_attach(result, NULL, simplecmdNode);
	return result;
}

t_astree* CMD3()
{
	return SIMPLECMD();
}

t_astree* SIMPLECMD()
{
	tok_t* save = curtok;
	return SIMPLECMD1();
}

t_astree* SIMPLECMD1()
{
	t_astree	*tokenListNode;
	t_astree	*result;
	char		*pathname;

	if (!term(TOKEN, &pathname))
		return NULL;
	tokenListNode = TOKENLIST();
	result = malloc(sizeof(*result));
	dastreeset_type(result, NODE_CMDPATH);
	astreeset_data(result, pathname);
	astree_attach(result, NULL, tokenListNode);
	return result;
}

t_astree* TOKENLIST()
{
	tok_t		*save;
	t_astree	*node;

	save  = curtok;
	curtok = save;
	node = TOKENLIST1();
	if (node != NULL)
		return node;
	save  = curtok;
	curtok = save;
	node = TOKENLIST2();
	if (node != NULL)
		return node;
	return NULL;
}

t_astree* TOKENLIST1()
{
	t_astree* tokenListNode;
	t_astree* result;

	char* arg;
	if (!term(TOKEN, &arg))
		return NULL;
	tokenListNode = TOKENLIST();
	result = malloc(sizeof(*result));
	dastreeset_type(result, NODE_ARGUMENT);
	astreeset_data(result, arg);
	astree_attach(result, NULL, tokenListNode);
	return result;
}

t_astree* TOKENLIST2()
{
	return NULL;
}

int parse(lexer_t* lexbuf, t_astree** syntax_tree)
{
	if (lexbuf->ntoks == 0)
		return (-1);
	curtok = lexbuf->llisttok;
	*syntax_tree = CMDLINE();
	if (curtok != NULL && curtok->type != 0)
	{
		printf("Syntax Error near: %s\n", curtok->data);
		return (-1);
	}
	return (0);
}
