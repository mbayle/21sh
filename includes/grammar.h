/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 04:40:29 by mabayle           #+#    #+#             */
/*   Updated: 2019/12/03 06:05:26 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAMMAR_H
# define GRAMMAR_H

# include "lexer.h"

int     program(t_lex *lex);
int     program1(t_lex *lex);
int     program2(t_lex *lex);

int     complete_cmds(t_lex *lex);
int     complete_cmds1(t_lex *lex);
int     complete_cmds2(t_lex *lex);

int     complete_cmd(t_lex *lex);
int     complete_cmd1(t_lex *lex);
int     complete_cmd2(t_lex *lex);

int     list(t_lex *lex);
int     list1(t_lex *lex);
int     list2(t_lex *lex);

int     and_or(t_lex *lex);
int     and_or1(t_lex *lex);
int     and_or2(t_lex *lex);
int     and_or3(t_lex *lex);

int     pipeline(t_lex *lex);
int     pipeline1(t_lex *lex);
int     pipeline2(t_lex *lex);

int     pipe_sequence(t_lex *lex);
int     pipe_sequence1(t_lex *lex);
int     pipe_sequence2(t_lex *lex);

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
 