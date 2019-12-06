/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 02:38:23 by mabayle           #+#    #+#             */
/*   Updated: 2019/12/06 07:08:38 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grammar.h"

/*
** Objectif de la fonction : balancing function for all case (io_redirect)
** Valeur de retour : return 1 if match | else return 0
*/
int     io_redirect(t_lex *lex)
{
    //ft_putendl("                                                                io_redirect1 -> ");
    if (io_redirect1(lex) == 1)
        return (1);
    //ft_putendl("                                                                io_redirect2 -> ");
    if (io_redirect2(lex) == 1)
        return (1);
    //ft_putendl("                                                                io_redirect3 -> ");
    if (io_redirect3(lex) == 1)
        return (1);
    //ft_putendl("                                                                io_redirect4 -> ");
    if (io_redirect4(lex) == 1)
        return (1);
    else
        //ft_putendl("                                                                io_redirect else -> ");
        return (0);
}

/*
** Objectif de la fonction : check if lex->token == IO_NUMBER et io_file ok
** Valeur de retour : return 1 if match | else return 0
*/
int     io_redirect1(t_lex *lex)
{
    //ft_putendl("                                                                    io_redirect1 -> ");
    return (lex->token == IO_NUMBER && io_file(lex) == 1 ? 1 : 0);
}

/*
** Objectif de la fonction : check if lex->token == IO_NUMBER et io_here ok
** Valeur de retour : return 1 if match | else return 0
*/
int     io_redirect2(t_lex *lex)
{
    //ft_putendl("                                                                     io_redirect2 -> ");
    return (lex->token == IO_NUMBER && io_here(lex) == 1 ? 1 : 0);
}

/*
** Objectif de la fonction : check if io_file is ok
** Valeur de retour : return 1 if match | else return 0
*/
int     io_redirect3(t_lex *lex)
{
    //ft_putendl("                                                                     io_redirect3 -> ");
    return (io_file(lex) == 1 ? 1 : 0);
}

/*
** Objectif de la fonction : check if io_here is ok
** Valeur de retour : return 1 if match | else return 0
*/
int     io_redirect4(t_lex *lex)
{
    //ft_putendl("                                                                            io_redirect4 -> ");
    return (io_here(lex) == 1 ? 1 : 0);
}