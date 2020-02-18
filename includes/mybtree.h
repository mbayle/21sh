/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mybtree.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 23:40:49 by mabayle           #+#    #+#             */
/*   Updated: 2020/02/18 02:52:45 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MYBTREE_H
# define MYBTREE_H

# include "projectinclude.h"

/*
** ast.c
*/
void				browse_ast(t_ast *ast);
void				sub_split(t_ast *ast, int priority);
void				print_debug(t_ast *ast, int pad);
t_ast				*beta_ast(t_ast *ast, int priority);
int					build_ast(t_lex *lex, t_ast **ast);

/*
** ast_utils.c
*/
t_ast				*init_node(t_lex *lex, char *root);
void				init_priority(t_lex *lex);
t_ast				*no_root(t_lex *lex, t_ast *ast);

/*
** print_ast.c
*/
void				ft_print_value(t_ast *ast, char *side, int lvl);
void				ft_print_node(t_ast *ast, char *side, int lvl);
void				ft_print_ast(t_ast *ast, char *side, int lvl);
void				ft_putast(t_ast *ast);

/*
** process_ast.c
*/
t_lex				*split_lex2(t_lex *lex, int stop);
t_lex				*split_lex3(t_lex *lex, int start);
t_ast				*create_ast2(
	t_ast *ast, t_lex *current, t_lex *right, t_lex *left);
t_ast				*create_ast(t_ast *ast, int priority);
/*
********************************************************************************
*/

/*
** ast.c
*/
void				sub_split(t_ast *ast, int priority);
void				print_debug(t_ast *ast, int pad);
int					is_in_lexer(t_lex *lex, int priority);
t_ast				*beta_ast(t_ast *ast, int priority);
void				do_to_ast();
int					build_ast(t_lex *lex, t_ast **ast);

/*
** ast_utils.c
*/
t_ast				*init_node(t_lex *lex, char *root);
void				init_priority(t_lex *lex);
t_ast				*no_root(t_lex *lex, t_ast *ast);

/*
** print_ast.c
*/
void				ft_print_value(t_ast *ast, char *side, int lvl);
void				ft_print_node(t_ast *ast, char *side, int lvl);
void				ft_print_ast(t_ast *ast, char *side, int lvl);
void				ft_putast(t_ast *ast);

/*
** process_ast.c
*/
t_lex				*split_lex2(t_lex *lex, int stop);
t_lex				*split_lex3(t_lex *lex, int start);
t_ast				*create_ast2(
	t_ast *ast, t_lex *current, t_lex *right, t_lex *left);
t_ast				*create_ast(t_ast *ast, int priority);

#endif
