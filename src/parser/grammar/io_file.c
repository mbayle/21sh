/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_file.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 01:27:15 by mabayle           #+#    #+#             */
/*   Updated: 2020/01/21 06:00:46 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

/*
** Purpose of the function : test all cases (io_file)
** Valeur de retour : return 1 if match | else return 0
*/

int		io_file(t_lex *lex)
{
	if (lex->next)
	{
		if (lex->operator == LESS && filename(lex->next) == 1)
			return (1);
		if (lex->operator == LESS_AND && filename(lex->next) == 1)
			return (1);
		if (lex->operator == GREAT && filename(lex->next) == 1)
			return (1);
		if (lex->operator == GREAT_AND && filename(lex->next) == 1)
			return (1);
		if (lex->operator == DGREAT && filename(lex->next) == 1)
			return (1);
		if (lex->operator == LESS_GREAT && filename(lex->next) == 1)
			return (1);
		if (lex->operator == CLOBBER && filename(lex->next) == 1)
			return (1);
		else
			return (0);
	}
	else
		return (0);
}
