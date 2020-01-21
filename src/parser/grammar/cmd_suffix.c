/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_suffix.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 05:17:27 by mabayle           #+#    #+#             */
/*   Updated: 2020/01/21 02:09:37 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

/*
** Objectif de la fonction : balancing function for all case (cmd_suffix)
** Valeur de retour : return 1 if match | else return 0
*/

int		cmd_suffix(t_lex *lex)
{
	if (cmd_suffix1(lex) == 1)
		return (1);
	if (cmd_suffix2(lex) == 1)
		return (1);
	if (cmd_suffix3(lex) == 1)
		return (1);
	if (cmd_suffix4(lex) == 1)
		return (1);
	else
		return (0);
}

/*
** Objectif de la fonction : check if lex == cmd_suffix + io_redirect
** Valeur de retour : return 1 if match | else return 0
*/

int		cmd_suffix1(t_lex *lex)
{
	if (cmd_suffix3(lex) == 1 || cmd_suffix4(lex) == 1)
	{
		if (lex->next)
			return (io_redirect(lex->next) == 1 ? 1 : 0);
		else
			return (0);
	}
	else
		return (0);
}

/*
** Objectif de la fonction : check if lex == cmd_suffix + WORD
** Valeur de retour : return 1 if match | else return 0
*/

int		cmd_suffix2(t_lex *lex)
{
	if ((cmd_suffix3(lex) == 1 || cmd_suffix4(lex) == 1)
			&& lex->token == WORD)
		return (1);
	else
		return (0);
}

/*
** Objectif de la fonction : check if lex == io_redirec ok
** Valeur de retour : return 1 if match | else return 0
*/

int		cmd_suffix3(t_lex *lex)
{
	return (io_redirect(lex) == 1 ? 1 : 0);
}

/*
** Objectif de la fonction : check if lex == WORDß
** Valeur de retour : return 1 if match | else return 0
*/

int		cmd_suffix4(t_lex *lex)
{
	return (lex->token == WORD ? 1 : 0);
}
