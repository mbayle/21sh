#include "minishell.h"

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

static void		welcome4(int m)
{
	rbar(m);
	fp("do", NULL);
	sleep(1);
	es8(m + 6, "####");
	es8(m + 5, "####");
	es8(m + 4, "####");
	es8(m + 3, "####");
	es8(m + 2, "####");
	es8(m + 1, "####");
	ft_sleep(0);
	ft_putchar('#');
	fp("up", NULL);
	ft_sleep(0);
	ft_putchar('#');
	do_m(m + 6);
	ft_sleep(0);
	ft_putchar('#');
	fp("up", NULL);
	ft_sleep(0);
	ft_putchar('#');
	do_m(m + 7);
	ft_sleep(0);
	ft_putchar('#');
	fp("up", NULL);
	ft_sleep(0);
}

int		welcome(t_struct s)
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
	welcome4(m);
	welcome5(m);
	welcome6(m);
	welcome7(m);
	welcome8(m);
	welcome9(m);
	return (welcome10(m, s));
}
