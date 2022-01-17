#ifndef PARSER_H
# define PARSER_H

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef	enum
{
	NODE_PIPE 			= (1 << 0),
	NODE_BCKGRND 		= (1 << 1),
	NODE_SEQ 			= (1 << 2),
	NODE_REDIRECT_IN 	= (1 << 3),
	NODE_REDIRECT_OUT 	= (1 << 4),
	NODE_REDIRECT_D_IN 	= (1 << 5),
	NODE_REDIRECT_D_OUT = (1 << 6),
	NODE_CMDPATH		= (1 << 7),
	NODE_ARGUMENT		= (1 << 8),

	NODE_DATA 			= (1 << 9),
} NodeType;

enum TokenType{
	CHAR_GENERAL		= -1,
	CHAR_PIPE			= '|',
	CHAR_AMPERSAND		= '&',
	CHAR_QOUTE			= '\'',
	CHAR_DQUOTE			= '\"',
	CHAR_SEMICOLON		= ';',
	CHAR_WHITESPACE		= ' ',
	CHAR_ESCAPESEQUENCE = '\\',
	CHAR_TAB			= '\t',
	CHAR_NEWLINE		= '\n',
	CHAR_GREATER		= '>',
	CHAR_LESSER			= '<',
	CHAR_DBLGREATER		= 'O',
	CHAR_DBLLESSER		= 'I',
	CHAR_NULL			= 0,

	TOKEN				= -1,
};

typedef struct	astree
{
	int type;
	char* szData;
	struct astree* left;
	struct astree* right;

} 				t_astree;

t_astree		*CMDLINE(tok_t **curtok);

t_astree		*JOB(tok_t **curtok);
t_astree		*JOB1(tok_t **curtok);
t_astree		*JOB2(tok_t **curtok);

t_astree		*CMD(tok_t **curtok);
t_astree		*CMD1(tok_t **curtok);
t_astree		*CMD2(tok_t **curtok);
t_astree		*CMD11(tok_t **curtok);
t_astree		*CMD22(tok_t **curtok);
t_astree		*CMD3(tok_t **curtok);

t_astree		*SIMPLECMD(tok_t **curtok);
t_astree		*SIMPLECMD1(tok_t **curtok);

t_astree		*TOKENLIST(tok_t **curtok);
t_astree		*TOKENLIST1(tok_t **curtok);
t_astree		*TOKENLIST2(tok_t **curtok);

bool			term(int toketype, char **bufferptr, tok_t **curtok);

void 			astree_attach(t_astree* root, t_astree* leftNode, t_astree* rightNode);
void 			astreeset_type(t_astree* node, NodeType nodetype);
void 			astreeset_data(t_astree* node, char* data);
void 			astree_delete(t_astree* node);

#endif
