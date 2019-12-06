/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 02:15:41 by mabayle           #+#    #+#             */
/*   Updated: 2019/12/06 06:02:11 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grammar.h"

/*
** Objectif de la fonction : balancing function for all case (pipeline)
** Valeur de retour : return 1 if match | else return 0
*/
int     pipeline(t_lex *lex)
{
    //ft_putendl("                                    pipeline -> ");
    if (pipeline1(lex) == 1)
        return (1);
    if (pipeline2(lex) == 1)
        return (1);
    else
        return (0);
}

/*
** Objectif de la fonction : check if first char is "!" + pipe_sequence
** Valeur de retour : return 1 if match | else return 0
*/
int     pipeline1(t_lex *lex)
{
    //ft_putendl("                                        pipeline1 -> ");
    return (lex->value[0] == '!' && pipe_sequence(lex) == 1 ? 1 : 0);
}

/*
** Objectif de la fonction : check if lex == pipe_sequence
** Valeur de retour : return 1 if match | else return 0
*/
int     pipeline2(t_lex *lex)
{
    ////ft_putendl("                                            pipeline2 -> ");
    return (pipe_sequence(lex) == 1 ? 1 : 0);
}