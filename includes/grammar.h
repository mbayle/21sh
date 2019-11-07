/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 04:40:29 by mabayle           #+#    #+#             */
/*   Updated: 2019/11/07 05:07:31 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAMMAR.H
# define GRAMMAR.H

#include "lexer.h"
#include "parser.h"

t_ast   *program(t_lex *current);
t_ast   *program1(void);
t_ast   *program2(void);

#endif