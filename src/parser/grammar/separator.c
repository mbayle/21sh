/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 04:08:34 by mabayle           #+#    #+#             */
/*   Updated: 2019/12/10 05:51:18 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grammar.h"

/*
** Objectif de la fonction : balancing function for all case (separator)
** Valeur de retour : return 1 if match | else return 0
*/
int     separator(t_lex *lex)
{
    if (separator1(lex) == 1)
        return (1);
    if (separator2(lex) == 1)
        return (1);
    else
        return (0);
}

/*
** Objectif de la fonction : check if lex->value = separator_op AND 
**                           linebreak
** Valeur de retour : return 1 if match | else return 0
*/
int     separator1(t_lex *lex)
{
    if (separator_op(lex) == 1 && linebreak(lex) == 1)
        return (1);
    else
        return (0);
}

/*
** Objectif de la fonction : check if lex->value = newline_list
** Valeur de retour : return 1 if match | else return 0
*/
int     separator2(t_lex *lex)
{
    if (newline_list(lex) == 1)
        return (1);
    else
        return (0);   
}