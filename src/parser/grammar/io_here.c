/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_here.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 23:49:12 by mabayle           #+#    #+#             */
/*   Updated: 2020/01/20 06:23:16 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

/*
** Objectif de la fonction : balancing function for all case (io_here)
** Valeur de retour : return 1 if match | else return 0
*/
int     io_here(t_lex *lex)
{
    //ft_putendl("                                                                                io_here -> ");
    if (io_here1(lex) == 1)
        return (1);
    if (io_here2(lex) == 1)
        return (1);
    else
        return (0);
}

/*
** Objectif de la fonction : check if lex->value = << + here_end
** Valeur de retour : return 1 if match | else return 0
*/
int     io_here1(t_lex *lex)
{
    //ft_putendl("                                                                                    io_here1 -> ");
    if (lex->operator == DLESS && (here_end(lex->next) == 1))
        return (1);
    else
        
        return (0);
}

/*
** Objectif de la fonction : check if lex->value = newline_list
** Valeur de retour : return 1 if match | else return 0
*/
int     io_here2(t_lex *lex)
{
    //ft_putendl("                                                                                    io_here2 -> ");
    if (lex->operator == DLESS_DASH && (here_end(lex->next) == 1))
        return (1);
    else
        return (0);
}