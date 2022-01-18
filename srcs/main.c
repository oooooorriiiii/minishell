/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymori <ymori@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 12:09:39 by ymori             #+#    #+#             */
/*   Updated: 2022/01/14 18:51:53 by ymori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"
#include "lexer.h"
#include <stdio.h>

int	main(void)
{
	t_lexer	*lex_list;

	lexer("echo abc", &lex_list);
	puts("**************************");
	lexer("echo\"abc\"|", &lex_list);
	puts("**************************");
	lexer("echo\"ab  c \"|", &lex_list);
	puts("**************************");
	// lexer("echo\"abc|", &lex_list);
	// puts("**************************");
	lexer("echo>>abc|>", &lex_list);
	puts("**************************");
	lexer("echo>>>abc|>", &lex_list);
	puts("**************************");
	lexer("echo>>>>abc|>", &lex_list);
	puts("**************************");
	lexer("echo> >>>abc|>", &lex_list);
	puts("**************************");
	lexer("echo>> >>abc|>", &lex_list);
	puts("**************************");
	lexer("echo>>> >abc|>", &lex_list);
	puts("**************************");
	lexer("echo><>>abc|>", &lex_list);
	puts("**************************");
	lexer("echo><> >abc|>", &lex_list);
	puts("**************************");
	lexer("echo>< >>abc|>", &lex_list);
	puts("**************************");
	lexer("echo> <>>abc|>", &lex_list);

	return (0);
}
