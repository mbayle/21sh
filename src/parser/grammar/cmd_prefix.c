/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_prefix.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 01:14:43 by mabayle           #+#    #+#             */
/*   Updated: 2019/12/06 06:02:11 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grammar.h"

/*
** Objectif de la fonction : balancing function for all case (cmd_prefix)
** Valeur de retour : return 1 if match | else return 0
*/
int     cmd_prefix(t_lex *lex)
{
    //ft_putendl("                                                        cmd_prefix1 -> ");
    if (cmd_prefix1(lex) == 1)
        return (1);
    //ft_putendl("                                                        cmd_prefix2 -> ");
    if (cmd_prefix2(lex) == 1)
        return (1);
    //ft_putendl("                                                        cmd_prefix3 -> ");
    if (cmd_prefix3(lex) == 1)
        return (1);
    //ft_putendl("                                                        cmd_prefix4 -> ");
    if (cmd_prefix4(lex) == 1)
        return (1);
    else
        //ft_putendl("                                                        cmd_prefix else -> ");
        return (0);
}

/*
** Objectif de la fonction : check if lex == cmd_prefix + io_redirect
** Valeur de retour : return 1 if match | else return 0
*/
int     cmd_prefix1(t_lex *lex)
{
    //ft_putendl("                                                            cmd_prefix1 -> ");
    if ((cmd_prefix3(lex) == 1 || cmd_prefix4(lex) == 1) 
            && io_redirect(lex->next) == 1)
        return (1);
    else
        return (0);
}

/*
** Objectif de la fonction : check if lex == cmd_prefix + ASSIGNEMENT_WORD
** Valeur de retour : return 1 if match | else return 0
*/
int     cmd_prefix2(t_lex *lex)
{
    //ft_putendl("                                                            cmd_prefix2 -> ");
    if ((cmd_prefix3(lex) == 1 || cmd_prefix4(lex) == 1) 
            && lex->token == ASSIGN_WORD)
        return (1);
    else
        return (0);
}

/*
** Objectif de la fonction : check if lex == io_redirec ok
** Valeur de retour : return 1 if match | else return 0
*/
int     cmd_prefix3(t_lex *lex)
{
    //ft_putendl("                                                            cmd_prefix3 -> ");
    return (io_redirect(lex) == 1 ? 1 : 0);
}

/*
** Objectif de la fonction : check if lex == ASSIGNEMENT_WORDß
** Valeur de retour : return 1 if match | else return 0
*/
int     cmd_prefix4(t_lex *lex)
{
    //ft_putendl("                                                            cmd_prefix4 -> ");
    return (lex->token == ASSIGN_WORD ? 1 : 0);
}