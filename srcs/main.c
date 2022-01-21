/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 12:09:39 by ymori             #+#    #+#             */
/*   Updated: 2022/01/21 14:38:31 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"
#include "lexer.h"
#include "parser.h"
#include <stdio.h>

int	main(void)
{
	t_lexer		*lex_list;
	t_astree	*ast;

	lexer("echo abc", &lex_list);
	parse(lex_list, &ast);
	lexer_free(&lex_list);
	puts("**************************");
	lexer("echo 42Tokyo > test.txt", &lex_list);
	parse(lex_list, &ast);
	lexer_free(&lex_list);
	// puts("**************************");
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
