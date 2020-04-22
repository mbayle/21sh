/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 02:15:41 by mabayle           #+#    #+#             */
/*   Updated: 2020/03/19 21:50:39 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

/*
** Purpose of the function : balancing function for all case (pipeline)
** Valeur de retour : return 1 if match | else return 0
*/

int		pipeline(t_lex *lex)
{
	if (pipeline1(lex) == 1)
		return (1);
	if (pipeline2(lex) == 1)
		return (1);
	else
		return (0);
}

/*
** Purpose of the function : check if first char is "!" + pipe_sequence
** Valeur de retour : return 1 if match | else return 0
*/

int		pipeline1(t_lex *lex)
{
	return (lex->value && (lex->value[0] == '!'
		&& pipe_sequence(lex) == 1) ? 1 : 0);
}

/*
** Purpose of the function : check if lex == pipe_sequence
** Valeur de retour : return 1 if match | else return 0
*/

int		pipeline2(t_lex *lex)
{
	return (pipe_sequence(lex) == 1 ? 1 : 0);
}
