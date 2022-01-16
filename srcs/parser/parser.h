#ifndef PARSER_H
# define PARSER_H

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

typedef struct	ASTreeNode
{
	int type;
	char* szData;
	struct ASTreeNode* left;
	struct ASTreeNode* right;

} 				t_ASTreeNode;

ASTreeNode*		CMDLINE();

ASTreeNode*		JOB();
ASTreeNode*		JOB1();
ASTreeNode*		JOB2();

ASTreeNode*		CMD();
ASTreeNode*		CMD1();
ASTreeNode*		CMD2();
ASTreeNode*		CMD3();

ASTreeNode*		SIMPLECMD();
ASTreeNode*		SIMPLECMD1();

ASTreeNode*		TOKENLIST();
ASTreeNode*		TOKENLIST1();
ASTreeNode*		TOKENLIST2();

#endif
