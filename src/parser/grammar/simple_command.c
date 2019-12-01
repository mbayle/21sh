/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 05:50:51 by mabayle           #+#    #+#             */
/*   Updated: 2019/12/01 06:29:33 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grammar.h"

/*
** Objectif de la fonction : balancing function for all case (simple_command)
** Valeur de retour : return 1 if match | else return 0
*/
int     simple_command(t_lex *lex)
{
    if (simple_command1(lex) == 1)
        return (1);
    if (simple_command2(lex) == 1)
        return (1);
    if (simple_command3(lex) == 1)
        return (1);
    if (simple_command4(lex) == 1)
        return (1);
    else
        return (0);
}

/*
** Objectif de la fonction : check if lex == cmd_prefix + cmd_word + cmd_suffix
** Valeur de retour : return 1 if match | else return 0
*/
int     simple_command1(t_lex *lex)
{
    
}