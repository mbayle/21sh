/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_help.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frameton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 23:01:08 by frameton          #+#    #+#             */
/*   Updated: 2020/02/04 04:10:59 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			es7(char *s, int m)
{
	ft_ptchar('\n');
	ft_marge(m);
	ft_putstr(s);
}

static int		help_ws(struct termios *term, int *m)
{
	struct winsize	sz;
	int				mh;

	ioctl(0, TIOCGWINSZ, &sz);
	if (sz.ws_col < 90 || sz.ws_row < 30)
	{
		ft_putstr(FRED"setcpt error : "WHITE);
		ft_putendl("window size too small.");
		return (0);
	}
	isatty(0);
	tcgetattr(0, &*term);
	(*term).c_lflag &= ~(ECHO);
	tcsetattr(0, TCSANOW, &*term);
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

int				exec_sethelp(void)
{
	int				ret;
	int				m;
	struct termios	term;
	char			buf[1];

	fp("cl", "vi");
	m = 0;
	ret = tgetent(NULL, getenv("TERM"));
	if (!(help_ws(&term, &m)))
		return (1);
	anim_cpt(m, 28, 42, 1);
	exec_help2(m);
	es7("Search history: ", m + 30);
	ft_putstr(MAGENTA"ctrl + r"WHITE);
	read(0, &buf, 1);
	return (exit_sethelp(&term));
}
