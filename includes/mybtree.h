/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mybtree.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 23:40:49 by mabayle           #+#    #+#             */
/*   Updated: 2020/01/20 06:14:10 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MYBTREE_H
# define MYBTREE_H

# include "projectinclude.h"

/*
** MAIN.c
*/
int		main(int argc, char **argv);
t_21sh	*init_shell(t_env *env, int debug);

/*
** AST.C
*/
int		build_ast(t_lex *lex, t_ast **ast);
void	init_priority(t_lex *lex);
t_ast	*init_node(t_lex *lex, char *root);
int		max_depth(t_ast *ast, int left_depth, int right_depth);
t_ast	*browse_ast(t_ast *ast, int find, int priority);
t_ast	*sub_split(t_ast *ast, int find, int priority);
t_ast	*no_root(t_lex *lex, t_ast *ast);
int		find_priority(t_ast *ast, int priority);

/*
** PROCESS_AST.C
*/
t_ast	*create_ast(t_ast *ast, int priority);
void	split_lex(t_ast *ast, int priority);
t_lex	*split_lex3(t_lex *lex, int start);
t_lex	*split_lex2(t_lex *lex, int stop);

/*
** PRINT_AST.C
*/
void	ft_putendl_col(char *str, char *color, char *colreset);
void	ft_padding(int padd);
void	ft_print_node(t_ast *ast, char *side, int lvl);
void	ft_print_ast(t_ast *ast, char *side, int lvl);
void	ft_putast(t_ast *ast);

#endif
