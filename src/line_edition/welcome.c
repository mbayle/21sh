/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   welcome.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 00:20:25 by frameton          #+#    #+#             */
/*   Updated: 2020/02/16 05:37:21 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

void			ps(char *s)
{
	ft_putstr(s);
}

static void		welcome2(int m)
{
	ft_putstr(CYAN);
	bar(m - 5, 1);
	cline(m);
	ft_sleep(1);
	ft_marge(m + 8);
	ps("''''''         ''''''''''''''''    '''''''''       '''''    '''''");
	upl(m);
	ft_sleep(1);
	ft_marge(m + 9);
	ps("/    /        /                            /       /   /    /   /");
	upl(m);
	ft_sleep(1);
	ft_marge(m + 10);
	ps("/    /         /    /_________     ____/   /       /   /''''/   /");
	upl(m);
	ft_sleep(1);
	ft_marge(m);
	ft_2putstr("'''''''''''/    /          /    ",
			"/                 /   /       /            /");
	upl(m);
	ft_sleep(1);
	ft_marge(m);
	ft_2putstr("/                /           /    /  ",
			"              /   /'''''  /   /____/   /");
	upl(m);
}

static void		welcome3(int m)
{
	ft_sleep(1);
	ft_marge(m);
	ft_2putstr(" /                /            /    /       ",
			"        /               /    /   /");
	upl(m);
	ft_sleep(1);
	ft_marge(m);
	ft_2putstr("  /    /_____/     /     '''     /    /        ",
			"       ________   ____     ____");
	upl(m);
	ft_sleep(1);
	ft_marge(m);
	ft_putstr("   /    /     /             /      /    /");
	upl(m);
	ft_sleep(1);
	ft_marge(m);
	ft_putstr("    /    /     /              /''''''/    /");
	upl(m);
	ft_sleep(1);
	ft_marge(m);
	ft_putstr("     /    /     /                         \\");
	upl(m);
	ft_sleep(1);
	ft_marge(m);
	ft_putstr("      _____      _____       ____________");
}

int				welcome(t_struct s)
{
	struct winsize	sz;
	int				m;
	int				h;

	tputs(tgetstr("vi", NULL), 1, ft_ptchar);
	ioctl(0, TIOCGWINSZ, &sz);
	if (sz.ws_col < 100 || sz.ws_row < 20)
		return (0);
	m = sz.ws_col - 80;
	m = m / 2;
	h = sz.ws_row + 11;
	h = h / 2;
	tputs(tgetstr("cl", NULL), 1, ft_ptchar);
	while (h--)
		tputs(tgetstr("do", NULL), 1, ft_ptchar);
	welcome2(m);
	welcome3(m);
	rbar(m);
	usleep(500000);
	fp("cl", NULL);
	print_prompt_bis(s.prompt, &s, 0);
	return (1);
}
