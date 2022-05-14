//
// Created by yuumo on 2022/05/11.
//

#include "../includes/minishell.h"
#include "../includes/lexer.h"

int lexer_test(t_lexer **lex_list)
{
	int i = 0;
	char *tmp[] = {
			"\"echo >> abc|>\"", \
		"echo \"echo $ USER\" >> test", \
		"echo \"echo >> $USER\" >> test", \
		"echo \"echo $U S E R\" >> test", \
		"echo \"echo $USER\" >> test", \
		"echo \"echo $USER\" >> test", \
		"echo \"echo $USER\" >> test", \
        NULL};
	while (tmp[i]) {
		lexer(tmp[i], lex_list);
		printf("\n%s ============\n", tmp[i]);
		print_token_list((*lex_list)->list);
		lexer_free(lex_list);
		i++;
	}
//	puts("**************************");
//	lexer("echo>>>abc|>", &lex_list);
//	puts("**************************");
//	lexer("echo>>>>abc|>", &lex_list);
//	puts("**************************");
//	lexer("echo> >>>abc|>", &lex_list);
//	puts("**************************");
//	lexer("echo>> >>abc|>", &lex_list);
//	puts("**************************");
//	lexer("echo>>> >abc|>", &lex_list);
//	puts("**************************");
//	lexer("echo><>>abc|>", &lex_list);
//	puts("**************************");
//	lexer("echo><> >abc|>", &lex_list);
//	puts("**************************");
//	lexer("echo>< >>abc|>", &lex_list);
//	puts("**************************");
//	lexer("echo> <>>abc|>", &lex_list);
	return (0);
}
