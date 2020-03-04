/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 04:21:06 by mabayle           #+#    #+#             */
/*   Updated: 2020/02/03 06:16:11 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

/*
** Color
*/
# define BLACK			"\033[0;30m"
# define L_GRAY			"\e[38;5;249m"
# define RED			"\033[0;31m"
# define L_YELLOW		"\e[38;5;143m"
# define PURPLE			"\033[0;35m"
# define L_BLUE			"\033[0;94m"
# define NC				"\033[0m"

/*
** ENUM
*/

enum					e_tok_type
{
	WORD,
	CONTROL_OPE,
	REDIR_OPE,
	IO_NUMBER,
	ASSIGN_WORD,
	NEW_LINE,
	UNKNOWN,
};

enum					e_operator
{
	OTHER,
	SEMIC,
	DSEMIC,
	PIPE,
	DPIPE,
	AND,
	DAND,
	LESS,
	DLESS,
	GREAT,
	DGREAT,
	LESS_AND,
	LESS_GREAT,
	DLESS_DASH,
	CLOBBER,
	GREAT_AND,
};

/*
** STRUCTURES
*/

typedef struct		s_lex
{
	char			*value;
	char			*hdoc;
	int				pos;
	int				hdoc_delim;
	enum e_tok_type	token;
	enum e_operator	operator;
	int				priority;
	struct s_lex	*next;
}					t_lex;

typedef struct		s_ast
{
	struct s_lex	*lex;
	char			*root;
	struct s_ast	*left;
	struct s_ast	*right;
}					t_ast;

typedef struct		s_21sh
{
	char			*line;
	t_lex			*lex;
	int				lex_size;
	t_ast			*ast;
	int				debug;
}					t_21sh;

t_21sh				*g_shell;

/*
** lexer.c
*/
int					find_end(int i, char *input);
int					end_case_index(t_lex *lex, char *input, int *io_nbr);
void				valid(t_lex **lex, char *input, int io, int i);
void				ft_lexer(t_lex **lex, char *input);

/*
** list_utils.c
*/
t_lex				*list_new(char *input);
void				list_add(t_lex **alst, t_lex *new);
t_lex				*lex_last(t_lex *lst);
void				lex_suppr_elem(t_lex **elem);
void				lexdel(t_lex **alst);

/*
** print_debug.c
*/
void				ft_print_header(t_lex **lex);
void				ft_print_control_op(enum e_operator op);
void				ft_print_redir_op(enum e_operator op);
void				ft_print_token(t_lex **lex);
void				ft_print_debug(t_lex **lex);

/*
** type_token.c
*/
void				is_operator(t_lex *new);
void				is_redirection(t_lex *new);
void				is_assignword(t_lex *new);
void				token_type(t_lex *new, int io_nbr, int assignword);

/*
** utils.c
*/
int					check_redir(char *input);
int					check_operator(char *input);
int					quote_case(int i, char *input);
int					ft_is_separator(char c);
/*
********************************************************************************
*/

/*
** lexer.c
*/
int					find_end(int i, char *input);
int					end_case_index(t_lex *lex, char *input, int *io_nbr);
void				valid(t_lex **lex, char *input, int io, int i);
void				ft_lexer(t_lex **lex, char *input);

/*
** list_utils.c
*/
t_lex				*list_new(char *input);
void				list_add(t_lex **alst, t_lex *new);
t_lex				*lex_last(t_lex *lst);
void				lex_suppr_elem(t_lex **elem);
void				lexdel(t_lex **alst);

/*
** print_debug.c
*/
void				ft_print_header(t_lex **lex);
void				ft_print_control_op(enum e_operator op);
void				ft_print_redir_op(enum e_operator op);
void				ft_print_token(t_lex **lex);
void				ft_print_debug(t_lex **lex);

/*
** type_token.c
*/
void				is_operator(t_lex *new);
void				is_redirection(t_lex *new);
void				is_assignword(t_lex *new);
void				token_type(t_lex *new, int io_nbr, int assignword);

/*
** utils.c
*/
int					check_redir(char *input);
int					check_operator(char *input);
int					quote_case(int i, char *input);
int					ft_is_separator(char c);

#endif
