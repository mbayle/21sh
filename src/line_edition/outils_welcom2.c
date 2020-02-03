#include "minishell.h"

void	cline(int m)
{
	tputs(tgetstr("cr", NULL), 1, ft_ptchar);
	tputs(tgetstr("ce", NULL), 1, ft_ptchar);
	tputs(tgetstr("up", NULL), 1, ft_ptchar);
	bar(m - 5, 0);
	tputs(tgetstr("do", NULL), 1, ft_ptchar);
}

void	upl(int m)
{
	tputs(tgetstr("up", NULL), 1, ft_ptchar);
	cline(m);
}

void	fp(char *s, char *s2)
{
	tputs(tgetstr(s, NULL), 1, ft_ptchar);
	if (s2)
		tputs(tgetstr(s2, NULL), 1, ft_ptchar);
}

void	do_m(int m)
{
	tputs(tgetstr("do", NULL), 1, ft_ptchar);
	ft_vmarge(m);
}

void	ft_putstr_anim(char *s, int c)
{
	while (c--)
	{
		ft_putchar(*s);
		s++;
		usleep(20000);
	}
}
