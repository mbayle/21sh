/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 04:21:06 by mabayle           #+#    #+#             */
/*   Updated: 2019/08/21 04:11:08 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef enum    e_token_type
{
    WORD,
    NEW_LINE,
    NUMBER,
    // (... A completer)
}               t_token_type;

typedef enum    e_operator
{
    PIPE, // |
	AND, // &
	QUOTE, // '
    DQUOTE, // "
    SEMICOLON, // ;
    WHITESPACE,
    ESCAPE, // '\'
    TAB, // \t
    GREATER, // >
    DGREATER, // >>
    LESSER, // <
    DLESSER, // <<
}               t_operator;

typedef struct  s_token
{
    int         type;
    char        *value;
    t_token     *next;
}               t_token;

typedef struct  s_lexer
{
    t_token     *token;
    int         nb_token;
}               t_lexer;

#endif