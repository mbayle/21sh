/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 05:22:48 by mabayle           #+#    #+#             */
/*   Updated: 2020/01/21 07:04:46 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

/*
** Purpose of the function : Print header
** Return value : no return
*/

void	ft_print_header(t_lex **lex)
{
	ft_putstr(PURPLE);
	ft_putendl("Lexer debug :");
	ft_putstr(NC);
	ft_putstr(" -----------------------------------------------------------");
	ft_putendl("----------------------");
	ft_putstr("|             TOKEN            	 | PRIORITY | POSITION |");
	ft_putendl("    	VALUE		  |");
	ft_putstr(" -----------------------------------------------------------");
	ft_putendl("----------------------");
	ft_print_debug(lex);
}

/*
** Purpose of the function : Special case for control operator
** Return value : no return
*/

void	ft_print_control_op(enum e_operator op)
{
	ft_putstr("   CONTROL_OPE = ");
	if (op == OTHER)
		ft_putstr("   NOT A CONTROL_OPE                          ");
	else if (op == SEMIC)
		ft_putstr("SEMIC           ");
	else if (op == DSEMIC)
		ft_putstr("DSEMIC          ");
	else if (op == PIPE)
		ft_putstr("PIPE            ");
	else if (op == DPIPE)
		ft_putstr("DPIPE           ");
	else if (op == AND)
		ft_putstr("AND             ");
	else if (op == DAND)
		ft_putstr("DAND            ");
}

/*
** Purpose of the function : Special case for redirection operator
** Return value : no return
*/

void	ft_print_redir_op(enum e_operator op)
{
	ft_putstr("   REDIR_OPE = ");
	if (op == OTHER)
		ft_putstr("   NOT A REDIR_OPE                            ");
	else if (op == LESS)
		ft_putstr("LESS              ");
	else if (op == DLESS)
		ft_putstr("DLESS             ");
	else if (op == GREAT)
		ft_putstr("GREAT             ");
	else if (op == DGREAT)
		ft_putstr("DGREAT            ");
	else if (op == LESS_AND)
		ft_putstr("LESS_AND          ");
	else if (op == GREAT_AND)
		ft_putstr("GREAT_AND         ");
	else if (op == LESS_GREAT)
		ft_putstr("LESS_GREAT        ");
	else if (op == DLESS_DASH)
		ft_putstr("DLESS_DASH        ");
	else if (op == CLOBBER)
		ft_putstr("CLOBBER           ");
}

/*
** Purpose of the function : Default print type of token (except for control
**							and redirection operator)
** Return value : no return
*/

void	ft_print_token(t_lex **lex)
{
	if ((*lex)->token == WORD)
		ft_putstr("   WORD                          ");
	else if ((*lex)->token == CONTROL_OPE)
		ft_print_control_op((*lex)->operator);
	else if ((*lex)->token == REDIR_OPE)
		ft_print_redir_op((*lex)->operator);
	else if ((*lex)->token == IO_NUMBER)
		ft_putstr("   IO_NUMBER                     ");
	else if ((*lex)->token == ASSIGN_WORD)
		ft_putstr("   ASSIGN_WORD                   ");
	else if ((*lex)->token == NEW_LINE)
		ft_putstr("   NEW_LINE                      ");
	else if ((*lex)->token == UNKNOWN)
		ft_putstr("   UNKNOWN                       ");
}

/*
** Purpose of the function : Loop all over my list and print detailled view of
**							my list
** Return value : no return
*/

void	ft_print_debug(t_lex **lex)
{
	t_lex *tmp;

	tmp = (*lex);
	(*lex) = tmp;
	init_priority(*lex);
	while ((*lex))
	{
		ft_putstr(CYAN);
		ft_print_token(lex);
		ft_putstr(NC);
		write(1, "|     ", 6);
		ft_putstr(RED);
		ft_putnbr((*lex)->priority);
		ft_putstr(NC);
		write(1, "    |    ", 9);
		ft_putnbr((*lex)->pos);
		(*lex)->pos <= 9 ? write(1, "     |    ", 10)
			: write(1, "    |     ", 9);
		ft_putstr(L_BLUE);
		ft_putendl((*lex)->value);
		(*lex) = (*lex)->next;
	}
	ft_putstr(NC);
	write(1, "\n", 1);
	(*lex) = tmp;
}
