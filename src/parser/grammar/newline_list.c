/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newline_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 00:57:02 by mabayle           #+#    #+#             */
/*   Updated: 2019/12/07 06:33:13 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grammar.h"

/*
** Objectif de la fonction : balancing function for all case (newline_list)
** Valeur de retour : return 1 if match | else return 0
*/
int     newline_list(t_lex *lex)
{
    //ft_putendl("                newline_list -> ");
    if (newline_list1(lex) == 1)
        return (1);
    if (newline_list2(lex) == 1)
        return (1);
    else
        return (0);
}

/*
** Objectif de la fonction : check if lex->value == newline_list AND
                             lex->next->value == NEW_LINE
** Valeur de retour : return 1 if match | else return 0
*/
int     newline_list1(t_lex *lex)
{
    //ft_putendl("                    newline_list1 -> ");
    if (lex == NULL)
        return (0);  
    if (lex->next != NULL && (lex->token == NEW_LINE && lex->next->token ==  NEW_LINE))
        return (1);
    else
        return (0);
}

/*
** Objectif de la fonction : check if lex->value == NEW_LINE
** Valeur de retour : return 1 if match | else return 0
*/
int     newline_list2(t_lex *lex)
{
    //ft_putendl("                    newline_list2 -> ");
    if (lex == NULL)
        return (0);
    else
        return (lex->token == NEW_LINE ? 1 : 0);
}