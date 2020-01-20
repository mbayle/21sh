/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 01:46:22 by mabayle           #+#    #+#             */
/*   Updated: 2020/01/20 06:23:16 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

int     program(t_lex *lex)
{
    while(lex)
    {
        while (lex->token != UNKNOWN && lex->token != SEMIC 
            && lex->token != AND)
        {
            if (program1(lex) == 1)
                return (1);
            if (program2(lex) == 1)
                return (1);
            lex = lex->next;
        }
        lex = lex->next;
    }
    return (0);    
}

int     program1(t_lex *lex)
{
    //ft_putendl("     program1 -> ");
    if (linebreak(lex) == 1 && complete_cmds(lex) == 1 && linebreak(lex) == 1)
        return (1);
    else
        return (0);
}

int     program2(t_lex *lex)
{
    //ft_putendl("     program2 -> ");
    return (linebreak(lex) == 1 ? 1 : 0);
}