/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_help2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 23:00:01 by frameton          #+#    #+#             */
/*   Updated: 2020/03/03 22:09:01 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

void	exec_help2(int m)
{
	ft_putchar('\n');
	es9("BASIC COMMANDS\n", m + 36);
	es7("Cursor movement: ", m + 30);
	ft_putstr(MAGENTA"<- / ->\n"WHITE);
	es7("Word cursor movements: ", m + 24);
	ft_putstr(MAGENTA"opt + <- / ->\n"WHITE);
	es7("Up/down a line: ", m + 30);
	ft_putstr(MAGENTA"opt + ↓/↑\n"WHITE);
	es7("Go to line start/end: ", m + 20);
	ft_putstr(MAGENTA"home/end or fn + <-/->\n"WHITE);
	es7("Browse the order history: ", m + 27);
	ft_putstr(MAGENTA"↓/↑\n"WHITE);
	es7("Select part of the command line: ", m + 19);
	ft_putstr(MAGENTA"Shift + <-/->\n"WHITE);
	es7("Copy: ", m + 36);
	ft_putstr(MAGENTA"opt + d"WHITE);
	es7("Paste: ", m + 35);
	ft_putstr(MAGENTA"opt + p"WHITE);
	es7("Cut: ", m + 37);
	ft_putstr(MAGENTA"opt + r\n"WHITE);
	es7("Change the completion level: ", m + 18);
	ft_putstr(MAGENTA"\"setcpt\" command"WHITE);
	es7("Quickly change completion level: ", m + 23);
	ft_putstr(MAGENTA"f1/f2\n"WHITE);
}
