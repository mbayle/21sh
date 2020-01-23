/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complete_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 04:16:16 by mabayle           #+#    #+#             */
/*   Updated: 2020/01/23 04:48:20 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

/*
** Purpose of the function : balancing function for all case (complete_cmd)
** Valeur de retour : return 1 if match | else return 0
*/

int		complete_cmd(t_lex *lex)
{
	if (complete_cmd1(lex) == 1)
		return (1);
	if (complete_cmd2(lex) == 1)
		return (1);
	else
		return (0);
}

/*
** Purpose of the function : check if lex == list + separator_op
** Valeur de retour : return 1 if match | else return 0
*/

int		complete_cmd1(t_lex *lex)
{
	return (list(lex) == 1 && separator_op(lex) == 1 ? 1 : 0);
}

/*
** Purpose of the function : check if lex == list
** Valeur de retour : return 1 if match | else return 0
*/

int		complete_cmd2(t_lex *lex)
{
	return (list(lex) == 1 ? 1 : 0);
}
