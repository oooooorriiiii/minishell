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
	NODE_CMDPATH		= (1 << 5),
	NODE_ARGUMENT		= (1 << 6),

	NODE_DATA 			= (1 << 7),
} NodeType;

typedef struct	astree
{
	int type;
	char* szData;
	struct astree* left;
	struct astree* right;

} 				t_astree;

t_astree*		CMDLINE();

t_astree*		JOB();
t_astree*		JOB1();
t_astree*		JOB2();

t_astree*		CMD();
t_astree*		CMD1();
t_astree*		CMD2();
t_astree*		CMD3();

t_astree*		SIMPLECMD();
t_astree*		SIMPLECMD1();

t_astree*		TOKENLIST();
t_astree*		TOKENLIST1();
t_astree*		TOKENLIST2();

void 			astree_attach(t_astree* root, t_astree* leftNode, t_astree* rightNode);
void 			astreeset_type(t_astree* node, NodeType nodetype);
void 			astreeset_data(t_astree* node, char* data);
void 			astree_delete(t_astree* node);

#endif
