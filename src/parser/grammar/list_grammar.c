/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_grammar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 04:04:22 by mabayle           #+#    #+#             */
/*   Updated: 2019/12/09 23:42:05 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grammar.h"

int     list(t_lex *lex)
{
    //ft_putendl("                    list -> ");
    if (list1(lex) == 1)
        return (1);
    if (list2(lex) == 1)
        return (1);
    else
        return (0);
}

int     list1(t_lex *lex)
{
    //ft_putendl("                        list1 -> ");
    if (and_or(lex) == 1 && separator_op(lex) == 1 && and_or(lex) == 1)
        return (1);
    else
        return (0);
}

int     list2(t_lex *lex)
{
    //ft_putendl("                            list2 -> ");
    return (and_or(lex) == 1 ? 1 : 0);
}