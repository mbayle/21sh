/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 05:22:48 by mabayle           #+#    #+#             */
/*   Updated: 2019/12/06 07:36:21 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

void	ft_print_debug(t_lex **lex)
{
	if ((*lex)->token == WORD)
		ft_putstr("   WORD                          ");
	else if ((*lex)->token == CONTROL_OPE)
	{
		ft_putstr("   CONTROL_OPE = ");
		if ((*lex)->operator == OTHER)
			ft_putstr("   NOT A CONTROL_OPE                          ");
		else if ((*lex)->operator == SEMIC)
			ft_putstr("SEMIC           ");
		else if ((*lex)->operator == DSEMIC)
			ft_putstr("DSEMIC          ");
		else if ((*lex)->operator == PIPE)
			ft_putstr("PIPE            ");
		else if ((*lex)->operator == DPIPE)
			ft_putstr("DPIPE           ");
		else if ((*lex)->operator == AND)
			ft_putstr("AND             ");
		else if ((*lex)->operator == DAND)
			ft_putstr("DAND            ");
	}
	else if ((*lex)->token == REDIR_OPE)
	{
		ft_putstr("   REDIR_OPE = ");
		if ((*lex)->operator == OTHER)
			ft_putstr("   NOT A REDIR_OPE                            ");
		else if ((*lex)->operator == LESS)
			ft_putstr("LESS              ");
		else if ((*lex)->operator == DLESS)
			ft_putstr("DLESS             ");
		else if ((*lex)->operator == GREAT)
			ft_putstr("GREAT             ");
		else if ((*lex)->operator == DGREAT)
			ft_putstr("DGREAT            ");
		else if ((*lex)->operator == LESS_AND)
			ft_putstr("LESS_AND          ");
		else if ((*lex)->operator == GREAT_AND)
			ft_putstr("GREAT_AND         ");
		else if ((*lex)->operator == LESS_GREAT)
			ft_putstr("LESS_GREAT        ");
		else if ((*lex)->operator == DLESS_DASH)
			ft_putstr("DLESS_DASH        ");
		else if ((*lex)->operator == CLOBBER)
			ft_putstr("CLOBBER           ");
	}
	else if ((*lex)->token == IO_NUMBER)
		ft_putstr("   IO_NUMBER                     ");
	else if ((*lex)->token == ASSIGN_WORD)
		ft_putstr("   ASSIGN_WORD                   ");
	else if ((*lex)->token == NEW_LINE)
		ft_putstr("   NEW_LINE                      ");
	else if((*lex)->token == UNKNOWN)
		ft_putstr("   UNKNOWN                       ");
}