/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 01:46:22 by mabayle           #+#    #+#             */
/*   Updated: 2020/01/23 05:07:34 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

/*
** Purpose of the function : balancing function for all case (program)
** Valeur de retour : return 1 if match | else return 0
*/

int		program(t_lex *lex)
{
	while (lex)
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

/*
** Purpose of the function : check if lex == linebreak + complete_cmds +
**							linebreak
** Valeur de retour : return 1 if match | else return 0
*/

int		program1(t_lex *lex)
{
	if (linebreak(lex) == 1 && complete_cmds(lex) == 1 && linebreak(lex) == 1)
		return (1);
	else
		return (0);
}

/*
** Purpose of the function : check if lex == linebreak
** Valeur de retour : return 1 if match | else return 0
*/

int		program2(t_lex *lex)
{
	return (linebreak(lex) == 1 ? 1 : 0);
}
