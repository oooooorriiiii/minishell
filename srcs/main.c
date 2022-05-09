
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 12:09:39 by ymori             #+#    #+#             */
/*   Updated: 2022/02/06 10:56:06 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"
#include "lexer.h"
#include "utils.h"
#include "../includes/parser.h"
#include "../includes/execute.h"
#include "msh_env.h"
#include "msh_error.h"
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
//	size_t		i = 0;

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
//		print_token_list((*lex_list)->list);
//		lexer_data_expand(lex_list);
		if (parse(*lex_list, ast) != -1)
		{
			// print_syntax_tree(*ast);
//			free_set((void **)&((*ast)->szData), ast_data_expand((*ast)->szData));
			execute_syntax_tree(*ast);
		}
		// print_token_list(*lex_list);
		// print_syntax_tree(*ast);
		lexer_free(lex_list);
		astree_delete(*ast);
	}
}


void	minishell_test(char **input, t_lexer **lex_list, t_astree **ast)
{
	extern char **environ;

	g_minishell.env = create_envlist(environ);
	if (lexer(*input, lex_list) != STATUS_GENERAL)
		lexer_free(lex_list);
	print_token_list((*lex_list)->list);
	if (parse(*lex_list, ast) != -1)
		execute_syntax_tree(*ast);
	print_syntax_tree(*ast);
	lexer_free(lex_list);
	astree_delete(*ast);
}

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
	return (0);
}

int	main(void)
{
	t_lexer		*lex_list;
	t_astree	*ast;
	char		*input;

	init(&input, &lex_list, &ast);
//	lexer_test(&lex_list);
	minishell_loop(&input, &lex_list, &ast);
	return (0);
}

/*
int main(void)
{
	t_lexer		*lex_list;
	t_astree	*ast;
	char		*input;

	init(&input, &lex_list, &ast);
	input = "aaaa";
	minishell_test(&input, &lex_list, &ast);
	// system("leaks minishell");
	return (0);
}
*/