/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complete_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 01:38:07 by mabayle           #+#    #+#             */
/*   Updated: 2020/01/23 05:00:48 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

/*
** Purpose of the function : balancing function for all case (complete_cmds)
** Valeur de retour : return 1 if match | else return 0
*/

int		complete_cmds(t_lex *lex)
{
	if (complete_cmds1(lex) == 1)
		return (1);
	if (complete_cmds2(lex) == 1)
		return (1);
	else
		return (0);
}

/*
** Purpose of the function : check if lex == complete_cmd + newline_list +
**							complete_cmd
** Valeur de retour : return 1 if match | else return 0
*/

int		complete_cmds1(t_lex *lex)
{
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

/*
** Purpose of the function : check if lex == complete_cmd
** Valeur de retour : return 1 if match | else return 0
*/

int		complete_cmds2(t_lex *lex)
{
	return (complete_cmd(lex) == 1 ? 1 : 0);
}
