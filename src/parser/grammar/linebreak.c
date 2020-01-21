/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linebreak.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 03:43:06 by mabayle           #+#    #+#             */
/*   Updated: 2020/01/21 06:00:46 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

/*
** Purpose of the function : balancing function for all case (linebreak)
** Valeur de retour : return 1 if match | else return 0
*/

int		linebreak(t_lex *lex)
{
	if (linebreak1(lex) == 1)
		return (1);
	if (linebreak2(lex) == 1)
		return (1);
	else
		return (0);
}

/*
** Purpose of the function : check if lex->value = newline_list
** Valeur de retour : return 1 if match | else return 0
*/

int		linebreak1(t_lex *lex)
{
	if (newline_list(lex) == 1)
		return (1);
	else
		return (0);
}

/*
** Purpose of the function : check if lex->value exist ??
** Valeur de retour : return 1 if match | else return 0
*/

int		linebreak2(t_lex *lex)
{
	(void)lex;
	return (1);
}
