/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 01:46:22 by mabayle           #+#    #+#             */
/*   Updated: 2019/12/05 06:26:53 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grammar.h"

int     program(t_lex *lex)
{
    ft_putstr("[DEBUG][PROGRAM] Value de lex : ");
    ft_putendl(lex->value);
    if(lex != NULL)
    {
        ft_putendl("Program -> ");
        if (program1(lex) == 1)
        {
            ft_putendl("OK");
            return (1);
        }    
        if (program2(lex) == 1)
        {
            ft_putendl("OK");
            return (1);
        }
        else
            return (0);
    }
    else
    {
        ft_putendl("LEX == NULL");
        return (1);
    }  
}

int     program1(t_lex *lex)
{
    ft_putendl("     program1 -> ");
    if (linebreak(lex) == 1 && complete_cmds(lex) == 1 && linebreak(lex) == 1)
        return (1);
    else
        return (0);
}

int     program2(t_lex *lex)
{
    ft_putendl("     program2 -> ");
    return (linebreak(lex) == 1 ? 1 : 0);
}