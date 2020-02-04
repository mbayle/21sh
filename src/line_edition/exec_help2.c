/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_help2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frameton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 23:00:01 by frameton          #+#    #+#             */
/*   Updated: 2020/02/03 23:05:32 by frameton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		exit_sethelp(struct termios *term)
{
	isatty(0);
	tcgetattr(0, &*term);
	(*term).c_lflag |= ECHO;
	tcsetattr(0, TCSANOW, &*term);
	fp("ve", "cl");
	return (1);
}

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
