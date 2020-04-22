/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_help2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 23:00:01 by frameton          #+#    #+#             */
/*   Updated: 2020/02/16 23:09:34 by frameton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

static void	exec_help2_b(int m)
{
	clr_shell(g_jobcontrol.s.clr);
	ft_putstr("Shift + <-/->\n"WHITE);
	es7("Copy: ", m + 36);
	clr_shell(g_jobcontrol.s.clr);
	ft_putstr("opt + d"WHITE);
	es7("Paste: ", m + 35);
	clr_shell(g_jobcontrol.s.clr);
	ft_putstr("opt + p"WHITE);
	es7("Cut: ", m + 37);
	clr_shell(g_jobcontrol.s.clr);
	ft_putstr("opt + r\n"WHITE);
	es7("Change the completion level: ", m + 18);
	clr_shell(g_jobcontrol.s.clr);
	ft_putstr("\"setcpt\" command"WHITE);
	es7("Quickly change completion level: ", m + 23);
	clr_shell(g_jobcontrol.s.clr);
	ft_putstr("f1/f2\n"WHITE);
	es7("Quickly Change shell color: ", m + 25);
	clr_shell(g_jobcontrol.s.clr);
	ft_putstr("f3/f4"WHITE);
}

void		exec_help2(int m)
{
	ft_putchar('\n');
	es9("BASIC COMMANDS\n", m + 36);
	es7("Cursor movement: ", m + 30);
	clr_shell(g_jobcontrol.s.clr);
	ft_putstr("<- / ->\n"WHITE);
	es7("Word cursor movements: ", m + 24);
	clr_shell(g_jobcontrol.s.clr);
	ft_putstr("opt + <- / ->\n"WHITE);
	es7("Up/down a line: ", m + 30);
	clr_shell(g_jobcontrol.s.clr);
	ft_putstr("opt + ↓/↑\n"WHITE);
	es7("Go to line start/end: ", m + 20);
	clr_shell(g_jobcontrol.s.clr);
	ft_putstr("home/end or fn + <-/->\n"WHITE);
	es7("Browse the order history: ", m + 27);
	clr_shell(g_jobcontrol.s.clr);
	ft_putstr("↓/↑\n"WHITE);
	es7("Select part of the command line: ", m + 19);
	clr_shell(g_jobcontrol.s.clr);
	exec_help2_b(m);
}
