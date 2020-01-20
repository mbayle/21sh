/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mybtree.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 23:40:49 by mabayle           #+#    #+#             */
/*   Updated: 2019/12/17 04:35:05 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MYBTREE_H
# define MYBTREE_H

#include "lexer.h"

/*
** MAIN.c
*/
int     main(int argc, char **argv);
t_21sh	*init_shell(void);

/*
** AST.C
*/
int     build_ast(t_lex *lex, t_ast *ast);
void    init_priority(t_lex *lex);
t_ast   *init_node(t_lex *lex);

/*
** PROCESS_AST.C
*/
void    create_ast(t_ast *ast, int priority);
void    split_lex(t_ast *ast, int priority);

/*
** PRINT_AST.C
*/
void	ft_putendl_col(char *str, char *color, char *colreset);
void	ft_padding(int padd);
void	ft_print_node(t_ast *ast, char *side, int lvl);
void	ft_print_ast(t_ast *ast, char *side, int lvl);
void	ft_putast(t_ast *ast);

#endif