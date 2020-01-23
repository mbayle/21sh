/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 05:50:51 by mabayle           #+#    #+#             */
/*   Updated: 2020/01/23 05:11:54 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

/*
** Purpose of the function : balancing function for all case (simple_command)
** Valeur de retour : return 1 if match | else return 0
*/

int		simple_command(t_lex *lex)
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
** Purpose of the function : check if lex == cmd_prefix + cmd_word + cmd_suffix
** Valeur de retour : return 1 if match | else return 0
*/

int		simple_command1(t_lex *lex)
{
	return (cmd_prefix(lex) == 1 && cmd_word(lex) == 1 && cmd_suffix(lex) == 1
			? 1 : 0);
}

/*
** Purpose of the function : check if lex == cmd_prefix + cmd_word
** Valeur de retour : return 1 if match | else return 0
*/

int		simple_command2(t_lex *lex)
{
	return (cmd_prefix(lex) == 1 && cmd_word(lex) == 1 ? 1 : 0);
}

/*
** Purpose of the function : check if lex == cmd_name + cmd_suffix
** Valeur de retour : return 1 if match | else return 0
*/

int		simple_command3(t_lex *lex)
{
	return (cmd_suffix(lex) == 1 && cmd_suffix(lex) == 1 ? 1 : 0);
}

/*
** Purpose of the function : check if lex == cmd_prefix OR lex == cmd_name
** Valeur de retour : return 1 if match | else return 0
*/

int		simple_command4(t_lex *lex)
{
	return (cmd_prefix(lex) == 1 || cmd_name(lex) ? 1 : 0);
}
