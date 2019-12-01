/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 04:40:29 by mabayle           #+#    #+#             */
/*   Updated: 2019/12/01 05:57:02 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAMMAR.H
# define GRAMMAR.H

#include "lexer.h"
#include "parser.h"

int     simple_command(t_lex *lex);
int     simple_command1(t_lex *lex);
int     simple_command2(t_lex *lex);
int     simple_command3(t_lex *lex);
int     simple_command4(t_lex *lex);

int     cmd_name(t_lex *lex);

int     cmd_word(t_lex *lex);

int     cmd_prefix(t_lex *lex);
int     cmd_prefix1(t_lex *lex);
int     cmd_prefix2(t_lex *lex);
int     cmd_prefix3(t_lex *lex);
int     cmd_prefix4(t_lex *lex);

int     cmd_suffix(t_lex *lex);
int     cmd_suffix1(t_lex *lex);
int     cmd_suffix2(t_lex *lex);
int     cmd_suffix3(t_lex *lex);
int     cmd_suffix4(t_lex *lex);

int     io_redirect(t_lex *lex);
int     io_redirect1(t_lex *lex);
int     io_redirect2(t_lex *lex);
int     io_redirect3(t_lex *lex);
int     io_redirect4(t_lex *lex);

int     io_here(t_lex *lex);
int     io_here1(t_lex *lex);
int     io_here2(t_lex *lex);

int     io_file(t_lex *lex);

int     filename(t_lex *lex);

int     io_here(t_lex *lex);
int     io_here1(t_lex *lex);
int     io_here2(t_lex *lex);

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
 