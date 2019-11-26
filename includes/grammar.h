/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 04:40:29 by mabayle           #+#    #+#             */
/*   Updated: 2019/11/26 05:46:25 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAMMAR.H
# define GRAMMAR.H

#include "lexer.h"
#include "parser.h"

int     here_end(t_lex *lex);

int     newline_list(t_lex *lex);
int     newline_list1(t_lex *lex);
int     newline_list2(t_lex *lex);

int     linebreak(t_lex *lex);
int     linebreak1(t_lex *lex);
int     linebreak2(t_lex *lex);

int     separator_op(t_lex *lex);
int     separator_op1(t_lex *lex);
int     separator_op2(t_lex *lex);

int     separator(t_lex *lex);
int     separator1(t_lex *lex);
int     separator2(t_lex *lex);

#endif