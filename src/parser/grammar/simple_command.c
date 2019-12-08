/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 05:50:51 by mabayle           #+#    #+#             */
/*   Updated: 2019/12/08 10:48:23 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grammar.h"

/*
** Objectif de la fonction : balancing function for all case (simple_command)
** Valeur de retour : return 1 if match | else return 0
*/
int     simple_command(t_lex *lex)
{
    //ft_putendl("                                                    simple_command1 -> ");
    if (simple_command1(lex) == 1)
        return (1);
    //ft_putendl("                                                    simple_command2 -> ");
    if (simple_command2(lex) == 1)
        return (1);
    //ft_putendl("                                                    simple_command3 -> ");
    if (simple_command3(lex) == 1)
        return (1);
    //ft_putendl("                                                    simple_command4 -> ");
    if (simple_command4(lex) == 1)
        return (1);
    else
        //ft_putendl("                                                    simple_command else -> ");
        return (0);
}

/*
** Objectif de la fonction : check if lex == cmd_prefix + cmd_word + cmd_suffix
** Valeur de retour : return 1 if match | else return 0
*/
int     simple_command1(t_lex *lex)
{
    //ft_putendl("                                                        simple_command1 -> ");
    return (cmd_prefix(lex) == 1 && cmd_word(lex) == 1 && cmd_suffix(lex) == 1
                ? 1 : 0);
}

/*
** Objectif de la fonction : check if lex == cmd_prefix + cmd_word
** Valeur de retour : return 1 if match | else return 0
*/
int     simple_command2(t_lex *lex)
{
    //ft_putendl("                                                            simple_command2 -> ");
    return (cmd_prefix(lex) == 1 && cmd_word(lex) == 1 ? 1 : 0);
}

/*
** Objectif de la fonction : check if lex == cmd_name + cmd_suffix
** Valeur de retour : return 1 if match | else return 0
*/
int     simple_command3(t_lex *lex)
{
    //ft_putendl("                                                            simple_command3 -> ");
    return (cmd_suffix(lex) == 1 && cmd_suffix(lex) == 1 ? 1 : 0);
}

/*
** Objectif de la fonction : check if lex == cmd_prefix OR lex == cmd_name
** Valeur de retour : return 1 if match | else return 0
*/
int     simple_command4(t_lex *lex)
{
    //ft_putendl("                                                            simple_command4 -> ");
    return (cmd_prefix(lex) == 1 || cmd_name(lex) ? 1 : 0);
}