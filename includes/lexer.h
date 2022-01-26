#ifndef LEXER_H
# define LEXER_H

# include <stdbool.h>
# include "minishell.h"
# include "../libft/libft.h"

# include <stdio.h>

typedef enum	e_status
{
	STATUS_ERROR		= -2,
	STATUS_GENERAL		= -1,
	STATUS_QOUTE		= '\'',
	STATUS_DQUOTE		= '\"',
	STATUS_WHITESPACE	= ' ',
	STATUS_DBLESSER		= 'I',
}				t_status;

typedef struct	s_token
{
	t_token_type	type;
	char			*val;
	struct s_token	*next;
}				t_token_list;

typedef struct s_lexer
{
	int				len;
	t_token_list	*list;
}				t_lexer;

// lexer_utils.c
t_lexer	*lexer_new(t_token_list *token_list);
void	lexer_free(t_lexer **lexer);

// is_quote.c
bool	is_quote(char c);
int		ft_isblank(int c);
bool	is_operator(char *element);

// lexer.c
t_status	lexer(char *original_line, t_lexer **lex_list);

// operator_analysis.c
void		literal_process(t_list **token_list, char **token, \
								t_token_list **ret_list);
t_status	operetor_analysis(t_list **token_list, char *token, \
								t_token_list *ret_list, char *element);

// token_split_to_list.c
void	free_set(void **dst, void *src);
t_list	*token_split_to_list(char *line);

// token_list_utils.c
t_token_list	*token_listnew(char *token, t_token_type token_type);
void			token_list_add_back(t_token_list **lst, t_token_list *new_elem);

// token_list_clear.c
void			token_list_delone(t_token_list *lst);
void			token_list_clear(t_token_list **lst);

// helper.c
void	list_print(t_list *list);
void	print_token_list(t_token_list *list);

// others
void	ft_fatal(char *errmsg);
void	merge_redirections(t_list *tokens);

#endif