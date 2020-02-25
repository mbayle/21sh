/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 01:57:25 by mabayle           #+#    #+#             */
/*   Updated: 2020/02/19 04:28:07 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"
/*
********************************************************************************
*/

/*
** expansion.c
*/
char				*value_env(char *input, int i);
char				*echo_verify_expand(char *input);
char				*dollar_expand(char *value);
char				*tilde_expand(char *value);
void				verify_expansion(t_lex *lex);

/*
** parser.c
*/
t_lex				*next_token(t_lex *lex);
char				*check_tokenerror(t_lex *lex);
int					ft_parse(t_lex **lex);

#endif
