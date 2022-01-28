
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
#include "parser.h"
#include "execute.h"
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
		lexer_free(lex_list);
	}
}

int	main(void)
{
	t_lexer		*lex_list;
	t_astree	*ast;
	char		*input;

	init(&input, &lex_list, &ast);
	minishell_loop(&input, &lex_list, &ast);

	lexer("echo abc", &lex_list);
	parse(lex_list, &ast);
	lexer_free(&lex_list);
	puts("**************************");
	lexer("echo 42Tokyo > test.txt", &lex_list);
	parse(lex_list, &ast);
	lexer_free(&lex_list);
	puts("**************************");
	lexer("pwd", &lex_list);
	parse(lex_list, &ast);
	lexer_free(&lex_list);
	execute_syntax_tree(ast);
	astree_delete(ast);
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
