/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complete_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 01:38:07 by mabayle           #+#    #+#             */
/*   Updated: 2019/12/09 23:42:05 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grammar.h"

int     complete_cmds(t_lex *lex)
{
    //ft_putendl("        complete_cmds -> ");
    if (complete_cmds1(lex) == 1)
        return (1);
    if (complete_cmds2(lex) == 1)
        return (1);
    else
        return (0);
}

int     complete_cmds1(t_lex *lex)
{
    //ft_putendl("            complete_cmds1 -> ");
    if (lex->next)
    {
        if (complete_cmd(lex) == 1 && (newline_list(lex->next) == 1 
        || complete_cmd(lex) == 1))
            return (1);
        else
            return (0);
    }
    else
        return (0);
}

int     complete_cmds2(t_lex *lex)
{
    //ft_putendl("            complete_cmds2 -> ");
    return (complete_cmd(lex) == 1 ? 1 : 0);
}