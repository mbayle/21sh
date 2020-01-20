/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_sequence.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 00:22:25 by mabayle           #+#    #+#             */
/*   Updated: 2020/01/20 06:23:16 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

/*
** Objectif de la fonction : balancing function for all case (pipe_sequence)
** Valeur de retour : return 1 if match | else return 0
*/
int     pipe_sequence(t_lex *lex)
{
    //ft_putendl("                                            pipe_sequence -> ");
    if (pipe_sequence1(lex) == 1)
        return (1);
    if (pipe_sequence2(lex) == 1)
        return (1);
    else
        return (0);
}

/*
** Objectif de la fonction : check if lex == simple_command + '|' +
**                           linebreak + simple_command
** Valeur de retour : return 1 if match | else return 0
*/
int     pipe_sequence1(t_lex *lex)
{
    //ft_putendl("                                                pipe_sequence1 -> ");
    if(lex->next)
    {
        if (simple_command(lex) == 1 && lex->next->operator == PIPE 
        && linebreak(lex) == 1 && simple_command(lex) == 1)
            return (1);
        else
            return (0);
    }
    else
        return (0);
}

/*
** Objectif de la fonction : check if lex == simple_command
** Valeur de retour : return 1 if match | else return 0
*/
int     pipe_sequence2(t_lex *lex)
{
    //ft_putendl("                                                    pipe_sequence2 -> ");
    return (simple_command(lex) == 1 ? 1 : 0);
}