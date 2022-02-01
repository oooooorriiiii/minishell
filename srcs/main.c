
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymori <ymori@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 12:09:39 by ymori             #+#    #+#             */
/*   Updated: 2022/01/27 03:48:51 by ymori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"
#include "lexer.h"
#include "utils.h"
#include "../includes/parser.h"
#include "../includes/execute.h"
#include "msh_env.h"
#include <stdio.h>
#include <errno.h>

t_minishell g_minishell = {};

void	init(char **input, t_lexer **lex_list, t_astree **ast)
{
	errno = 0;
	*input = NULL;
	*lex_list = NULL;
	*ast = NULL;
}

void	minishell_loop(char **input, t_lexer **lex_list, t_astree **ast)
{
	extern char **environ;
	size_t		i = 0;

	g_minishell.env = create_envlist(environ);

	while (true)
	{
		free_set((void **)input, NULL);
		*input = readline("minishell> ");
		if (*input == NULL)
			exit(g_minishell.exit_status);
		if (ft_strlen(*input) == 0)
			continue ;
		add_history(*input);
		if (lexer(*input, lex_list) != STATUS_GENERAL)
		{
			lexer_free(lex_list);
			continue ;
		}
		// TODO: parse
		parse(*lex_list, ast);
//		printf("===================================================\n\n\n\n");
		lexer_free(lex_list);
		execute_syntax_tree(*ast);
		astree_delete(*ast);
	}
}

int	main(void)
{
	t_lexer		*lex_list;
	t_astree	*ast;
	char		*input;

	init(&input, &lex_list, &ast);
	minishell_loop(&input, &lex_list, &ast);

//	char *txt[9];
//	int i = 1;
//
//	txt[0] = "ls -a | grep 42Tokyo | wc -l";
//	// txt[0] = "pwd";
//
//	txt[1] = "echo \"I like $sport\"";
//	txt[2] = "echo \'I like $sport\'";
//	txt[3] = "echo I like $nothing";
//	txt[4] = "echo \"I like $nothing\"";
//	txt[5] = "echo \'I like $nothing\'";
//	txt[6] = "echo aaaaaaa$sport****";
//	txt[7] = "echo a ba cfd";
//	txt[8] = NULL;

	/*
	init(&input, &lex_list, &ast);
	printf("\n\n\n■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ [[[[[ %s ]]]]] ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n", txt[0]);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n\n");
	lexer(txt[0], &lex_list);
	parse(lex_list, &ast);
	lexer_free(&lex_list);
	printf("==============================================================\n");
	printf("\n\n");
	execute_syntax_tree(ast);
	astree_delete(ast);
	*/


//	while (txt[i])
//	{
//		init(&input, &lex_list, &ast);
//		printf("\n\n\n■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
//		printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ [[[[[ %s ]]]]] ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n", txt[i]);
//		printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n\n");
//		lexer(txt[i], &lex_list);
//		parse(lex_list, &ast);
//		lexer_free(&lex_list);
//		printf("==============================================================\n");
//		printf("\n\n");
//		execute_syntax_tree(ast);
//		astree_delete(ast);
//		i++;
//	}


//	puts("**************************");
//	lexer("echo 42Tokyo > test.txt", &lex_list);
//	parse(lex_list, &ast);
//	lexer_free(&lex_list);
//	puts("**************************");
//	lexer("pwd", &lex_list);
//	parse(lex_list, &ast);
//	lexer_free(&lex_list);
//	execute_syntax_tree(ast);
//	astree_delete(ast);
	// lexer("echo\"ab  c \"|", &lex_list);
	// puts("**************************");
	// // lexer("echo\"abc|", &lex_list);
	// // puts("**************************");
	// lexer("echo>>abc|>", &lex_list);
	// puts("**************************");
	// lexer("echo>>>abc|>", &lex_list);
	// puts("**************************");
	// lexer("echo>>>>abc|>", &lex_list);
	// puts("**************************");
	// lexer("echo> >>>abc|>", &lex_list);
	// puts("**************************");
	// lexer("echo>> >>abc|>", &lex_list);
	// puts("**************************");
	// lexer("echo>>> >abc|>", &lex_list);
	// puts("**************************");
	// lexer("echo><>>abc|>", &lex_list);
	// puts("**************************");
	// lexer("echo><> >abc|>", &lex_list);
	// puts("**************************");
	// lexer("echo>< >>abc|>", &lex_list);
	// puts("**************************");
	// lexer("echo> <>>abc|>", &lex_list);

	return (0);
}
