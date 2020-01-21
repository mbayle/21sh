/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 03:37:19 by mabayle           #+#    #+#             */
/*   Updated: 2020/01/21 01:57:23 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

int		and_or(t_lex *lex)
{
	if (and_or1(lex) == 1)
		return (1);
	if (and_or2(lex) == 1)
		return (1);
	if (and_or3(lex) == 1)
		return (1);
	else
		return (0);
}

int		and_or1(t_lex *lex)
{
	if (lex->next)
	{
		if (pipeline(lex) == 1 && lex->next->token == DAND && linebreak(lex)
				&& pipeline(lex) == 1)
			return (1);
		else
			return (0);
	}
	else
		return (0);
}

int		and_or2(t_lex *lex)
{
	if (lex->next)
	{
		if (pipeline(lex) == 1 && lex->next->token == DPIPE && linebreak(lex)
				&& pipeline(lex) == 1)
			return (1);
		else
			return (0);
	}
	else
		return (0);
}

int		and_or3(t_lex *lex)
{
	return (pipeline(lex) == 1 ? 1 : 0);
}
