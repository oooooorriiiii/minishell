/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 12:09:39 by ymori             #+#    #+#             */
/*   Updated: 2022/05/16 09:23:42 by sosugimo         ###   ########.fr       */
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
#include "msh_signal.h"
#include <stdio.h>
#include <errno.h>

t_minishell	g_minishell = {};

void	init(char **input, t_lexer **lex_list, t_astree **ast)
{
	extern char	**environ;

	errno = 0;
	*input = NULL;
	*lex_list = NULL;
	*ast = NULL;
	signal_init(signal_handler_prompt, SIG_IGN, NULL);
	g_minishell.env = create_envlist(environ);
}

void	minishell_loop(char **input, t_lexer **lex_list, t_astree **ast)
{
	while (true)
	{
		free_set((void **)input, NULL);
		*input = readline("minishell$ ");
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
		{
			expansion(*ast);
			execute_syntax_tree(*ast);
		}
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
	return (0);
}
