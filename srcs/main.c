/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 12:09:39 by ymori             #+#    #+#             */
/*   Updated: 2022/02/05 17:54:09 by sosugimo         ###   ########.fr       */
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
		if (parse(*lex_list, ast) != -1)
			execute_syntax_tree(*ast);
		// print_token_list(ret_list);
		// print_syntax_tree(*ast);
		lexer_free(lex_list);
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

	/*
	char *test = "echo aaaa$?aaaaa";
	init(&input, &lex_list, &ast);
	printf("\n\n\n■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ [[[[[ %s ]]]]] ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n", test);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n\n");
	lexer(test, &lex_list);
	parse(lex_list, &ast);
	lexer_free(&lex_list);
	printf("==============================================================\n");
	printf("\n\n");
	execute_syntax_tree(ast);
	astree_delete(ast);
	*/

/*
	while (txt[i])
	{
		init(&input, &lex_list, &ast);
		printf("\n\n\n■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		printf("   ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ [[[[[ %s ]]]]] ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ \n", txt[i]);
		printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n\n");
		lexer(txt[i], &lex_list);
		parse(lex_list, &ast);
		lexer_free(&lex_list);
		printf("minishell> ");
		execute_syntax_tree(ast);
		astree_delete(ast);
		i++;
	}
	printf("\n\n");

	printf("exit_status :   %d\n", g_minishell.exit_status);
*/
	return (0);
}
