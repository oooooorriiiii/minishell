#include "parser.h"

tok_t* curtok = NULL;

bool term(int toketype, char** bufferptr)
{
	if (curtok == NULL)
		return false;

	if (curtok->type == toketype)
	{
		if (bufferptr != NULL) {
			*bufferptr = malloc(strlen(curtok->data) + 1);
			strcpy(*bufferptr, curtok->data);
		}
		curtok = curtok->next;
		return true;
	}

	curtok = curtok->next;
	return false;
}

ASTreeNode* CMDLINE()
{
	return JOB();
}

ASTreeNode* CMDLINE5()
{
	return JOB();
}

ASTreeNode* JOB()
{
	tok_t* save = curtok;

	ASTreeNode* node;

	if ((curtok = save, node = JOB1()) != NULL)
		return node;

	if ((curtok = save, node = JOB2()) != NULL)
		return node;

	return NULL;
}

ASTreeNode* JOB1()
{
	ASTreeNode* cmdNode;
	ASTreeNode* jobNode;
	ASTreeNode* result;

	if ((cmdNode = CMD()) == NULL)
		return NULL;

	if (!term(CHAR_PIPE, NULL)) {
		ASTreeNodeDelete(cmdNode);
		return NULL;
	}

	if ((jobNode = JOB()) == NULL) {
		ASTreeNodeDelete(cmdNode);
		return NULL;
	}

	result = malloc(sizeof(*result));
	ASTreeNodeSetType(result, NODE_PIPE);
	ASTreeAttachBinaryBranch(result, cmdNode, jobNode);

	return result;
}

ASTreeNode* JOB2()
{
	return CMD();
}

ASTreeNode* CMD()
{
	tok_t* save = curtok;

	ASTreeNode* node;

	if ((curtok = save, node = CMD1()) != NULL)
		return node;

	if ((curtok = save, node = CMD2()) != NULL)
		return node;

	if ((curtok = save, node = CMD3()) != NULL)
		return node;

	return NULL;
}

ASTreeNode* CMD1()
{
	ASTreeNode* simplecmdNode;
	ASTreeNode* result;

	if ((simplecmdNode = SIMPLECMD()) == NULL)
		return NULL;

	if (!term(CHAR_LESSER, NULL)) {
		ASTreeNodeDelete(simplecmdNode);
		return NULL;
	}

	char* filename;
	if (!term(TOKEN, &filename)) {
		free(filename);
		ASTreeNodeDelete(simplecmdNode);
		return NULL;
	}

	result = malloc(sizeof(*result));
	ASTreeNodeSetType(result, NODE_REDIRECT_IN);
	ASTreeNodeSetData(result, filename);
	ASTreeAttachBinaryBranch(result, NULL, simplecmdNode);

	return result;
}

ASTreeNode* CMD2()
{
	ASTreeNode* simplecmdNode;
	ASTreeNode* result;

	if ((simplecmdNode = SIMPLECMD()) == NULL)
		return NULL;

	if (!term(CHAR_GREATER, NULL)) {
		ASTreeNodeDelete(simplecmdNode);
		return NULL;
	}

	char* filename;
	if (!term(TOKEN, &filename)) {
		free(filename);
		ASTreeNodeDelete(simplecmdNode);
		return NULL;
	}

	result = malloc(sizeof(*result));
	ASTreeNodeSetType(result, NODE_REDIRECT_OUT);
	ASTreeNodeSetData(result, filename);
	ASTreeAttachBinaryBranch(result, NULL, simplecmdNode);

	return result;
}

ASTreeNode* CMD3()
{
	return SIMPLECMD();
}

ASTreeNode* SIMPLECMD()
{
	tok_t* save = curtok;
	return SIMPLECMD1();
}

ASTreeNode* SIMPLECMD1()
{
	ASTreeNode* tokenListNode;
	ASTreeNode* result;

	char* pathname;
	if (!term(TOKEN, &pathname))
		return NULL;

	tokenListNode = TOKENLIST();

	result = malloc(sizeof(*result));
	ASTreeNodeSetType(result, NODE_CMDPATH);
	ASTreeNodeSetData(result, pathname);
	ASTreeAttachBinaryBranch(result, NULL, tokenListNode);

	return result;
}

ASTreeNode* TOKENLIST()
{
	tok_t* save = curtok;

	ASTreeNode* node;

	if ((curtok = save, node = TOKENLIST1()) != NULL)
		return node;

	if ((curtok = save, node = TOKENLIST2()) != NULL)
		return node;

	return NULL;
}

ASTreeNode* TOKENLIST1()
{
	ASTreeNode* tokenListNode;
	ASTreeNode* result;

	char* arg;
	if (!term(TOKEN, &arg))
		return NULL;

	tokenListNode = TOKENLIST();

	result = malloc(sizeof(*result));
	ASTreeNodeSetType(result, NODE_ARGUMENT);
	ASTreeNodeSetData(result, arg);
	ASTreeAttachBinaryBranch(result, NULL, tokenListNode);

	return result;
}

ASTreeNode* TOKENLIST2()
{
	return NULL;
}

int parse(lexer_t* lexbuf, ASTreeNode** syntax_tree)
{
	if (lexbuf->ntoks == 0)
		return -1;

	curtok = lexbuf->llisttok;
	*syntax_tree = CMDLINE();

	if (curtok != NULL && curtok->type != 0)
	{
		printf("Syntax Error near: %s\n", curtok->data);
		return -1;
	}

	return 0;
}
