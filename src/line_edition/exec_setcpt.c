/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_setcpt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 00:58:15 by frameton          #+#    #+#             */
/*   Updated: 2020/03/12 13:17:12 by frameton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

void		exec_setcpt3(t_struct *s, int m)
{
	int		ret;
	char	buf[5];

	while ((ret = read(0, &buf, 5)))
	{
		if (buf[0] == 27 && buf[1] == 91 && buf[2] == 67)
		{
			tputs(tgetstr("cr", NULL), 1, ft_ptchar);
			ft_marge(m + 40);
			exec_setcpt4(s);
		}
		if (buf[0] == 27 && buf[1] == 91 && buf[2] == 68)
		{
			tputs(tgetstr("cr", NULL), 1, ft_ptchar);
			ft_marge(m + 40);
			exec_setcpt5(s);
		}
		if (buf[0] == '\n' || (buf[0] == 27 && ret == 1))
			break ;
		clr_shell(s->clr);
		ft_putnbr(s->cpt);
		ft_putstr(WHITE);
		tputs(tgetstr("le", NULL), 1, ft_ptchar);
	}
}

void		write_anim(int i, int clr)
{
	tputs(tgetstr("im", NULL), 1, ft_ptchar);
	clr_shell(clr);
	ft_putstr("_");
	fp("ei", "rc");
	while (i--)
		tputs(tgetstr("le", NULL), 1, ft_ptchar);
	clr_shell(clr);
	ft_putstr("_");
	tputs(tgetstr("rc", NULL), 1, ft_ptchar);
}

void		anim_cpt(int m, int lr, int c, int clr)
{
	int		s;
	int		i;

	i = 0;
	ft_marge(m + 42);
	clr_shell(clr);
	s = lr;
	while (c)
	{
		tputs(tgetstr("sc", NULL), 1, ft_ptchar);
		write_anim(i, clr);
		while (lr--)
			tputs(tgetstr("do", NULL), 1, ft_ptchar);
		lr = s;
		s = m + 42;
		while (s--)
			tputs(tgetstr("nd", NULL), 1, ft_ptchar);
		s = lr;
		tputs(tgetstr("sc", NULL), 1, ft_ptchar);
		write_anim(i, clr);
		while (lr--)
			tputs(tgetstr("up", NULL), 1, ft_ptchar);
		lr = s;
		++i;
		--c;
		usleep(10000);
	}
}

int			exec_setcpt(t_struct *s)
{
//	int				ret;
	int				m;

	m = 0;
	tgetent(NULL, getenv("TERM"));
	if (!(exec_setcpt8(s, &m)))
		return (1);
	anim_cpt(m, 28, 42, s->clr);
	ft_putchar('\n');
	ft_marge(m);
	clr_shell(s->clr);
	ft_putendl("                            COMPLETION CONFIGURATION"WHITE);
	ft_putendl("\n");
	ft_marge(m + 13);
	ft_putendl("Lvl 1 : Only manual completion is enabled, (TAB touch)\n");
	es9("Lvl 2 : Dynamic completion, effective with a single match\n", m + 11);
	ft_marge(m + 10);
	ft_putendl("Lvl 3 : Dynamic completion, effective with multiple matches\n");
	ft_marge(m + 10);
	ft_putendl("Lvl 4 : Automatic completion, effective with a single match\n");
	exec_setcpt6(s, m);
	fp("ve", NULL);
	return (0);
}
