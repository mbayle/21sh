/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_grammar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 04:04:22 by mabayle           #+#    #+#             */
/*   Updated: 2020/01/23 05:04:42 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

/*
** Purpose of the function : balancing function for all case (list)
** Valeur de retour : return 1 if match | else return 0
*/

int		list(t_lex *lex)
{
	if (list1(lex) == 1)
		return (1);
	if (list2(lex) == 1)
		return (1);
	else
		return (0);
}

/*
** Purpose of the function : check if lex = and_or + separator_op + and_or
** Valeur de retour : return 1 if match | else return 0
*/

int		list1(t_lex *lex)
{
	if (and_or(lex) == 1 && separator_op(lex) == 1 && and_or(lex) == 1)
		return (1);
	else
		return (0);
}

/*
** Purpose of the function : check if lex == and_or
** Valeur de retour : return 1 if match | else return 0
*/

int		list2(t_lex *lex)
{
	return (and_or(lex) == 1 ? 1 : 0);
}
