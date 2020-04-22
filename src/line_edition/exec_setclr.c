/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_setclr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 23:01:08 by frameton          #+#    #+#             */
/*   Updated: 2020/03/10 02:52:38 by frameton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

static int	clr_ws(int *m)
{
	struct winsize	sz;
	int				mh;

	ioctl(0, TIOCGWINSZ, &sz);
	if (sz.ws_col < 90 || sz.ws_row < 30)
	{
		ft_putstr(FRED"setclr error : "WHITE);
		ft_putendl("window size too small.");
		return (0);
	}
	tputs(tgetstr("vi", NULL), 1, ft_ptchar);
	tputs(tgetstr("cl", NULL), 1, ft_ptchar);
	*m = sz.ws_col - 84;
	mh = sz.ws_row - 29;
	*m = *m / 2;
	mh = mh / 2;
	while (mh--)
		tputs(tgetstr("do", NULL), 1, ft_ptchar);
	return (1);
}

static void	write_anim(int i, int clr)
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

static void	anim_cpt(int m, int lr, int ind, t_struct *st)
{
	int		s;
	int		i;
	int		c;

	i = 1;
	c = 42;
	ft_marge(m + 42);
	clr_shell(st->clr);
	s = lr;
	while (c)
	{
		tputs(tgetstr("sc", NULL), 1, ft_ptchar);
		write_anim(i, st->clr);
		anim_cpt2(&lr, &s, m);
		write_anim(i, st->clr);
		while (lr--)
			tputs(tgetstr("up", NULL), 1, ft_ptchar);
		lr = s;
		++i;
		--c;
		if (ind)
			usleep(10000);
	}
}

int			exec_setclr2(t_struct *s, int *m)
{
	int		ret;
	char	buf[5];

	while ((ret = read(0, &buf, 5)))
	{
		if (buf[0] == 27 && buf[1] == 91 && buf[2] == 65)
			s->clr--;
		if (buf[0] == 27 && buf[1] == 91 && buf[2] == 66)
			s->clr++;
		if (buf[0] == 27 && buf[1] == 91 && buf[2] == 68 && !s->ci)
			s->ci = 1;
		if (buf[0] == 27 && buf[1] == 91 && buf[2] == 67 && s->ci)
			s->ci = 0;
		if (buf[0] == '\n' || (buf[0] == 27 && ret == 1))
			break ;
		if (!clr_ws(m))
			return (1);
		exec_setclr(s, 0);
	}
	return (0);
}

int			exec_setclr(t_struct *s, int i)
{
	int		m;

	if (s->clr == 14 && (s->clr = 13))
		fp("bl", NULL);
	if (s->clr == -1 && !(s->clr = 0))
		fp("bl", NULL);
	fp("cl", "vi");
	m = 0;
	tgetent(NULL, getenv("TERM"));
	if (!(clr_ws(&m)))
		return (1);
	anim_cpt(m, 28, i, s);
	exec_clr2(m, s->clr, s->ci);
	if (i)
	{
		if (exec_setclr2(s, &m))
			return (1);
	}
	if (i)
		fp("ve", "cl");
	return (0);
}
