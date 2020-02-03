#include "minishell.h"

static void	init_lst_b(struct termios *term, t_struct *s)
{
	static int	wlcm;

	isatty(0);
	tcgetattr(0, &*term);
	(*term).c_lflag &= ~(ECHO);
	tcsetattr(0, TCSANOW, &*term);
	s->nl = 0;
	if (!wlcm && (wlcm = 1))
		welcome(*s);
}

static void	init_lst_b2(t_struct *s, char buf[5], int ret)
{
	if (buf[0] == 12 && ret == 1 && (buf[0] = '\n'))
		tputs(tgetstr("cl", NULL), 1, ft_ptchar);
	else
		write(1, "\n", 1);
	if (buf[0] == 9 && !s->lbg && !s->tmp)
	{
		tputs(tgetstr("cr", NULL), 1, ft_ptchar);
		tputs(tgetstr("up", NULL), 1, ft_ptchar);
		tputs(tgetstr("dl", NULL), 1, ft_ptchar);
		write(1, "\n", 1);
	}
	tputs(tgetstr("ei", NULL), 1, ft_ptchar);
	if (!s->lbg && s->tmp)
		s->lbg = s->tmp;
}

static int	init_lst_b3(t_struct *s, struct termios *term)
{
	while (s->tmp && s->tmp->next)
	{
		s->tmp = s->tmp->next;
		if (s->tmp && s->tmp->line > s->tmp->prev->line)
			tputs(tgetstr("do", NULL), 1, ft_ptchar);
	}
	isatty(0);
	tcgetattr(0, &*term);
	(*term).c_lflag |= ECHO;
	tcsetattr(0, TCSANOW, &*term);
	return (1);
}

int			init_lst(t_struct *s, int i, int r)
{
	char			buf[6];
	int				ret;
	struct winsize	sz;
	struct termios	term;

	init_lst_b(&term, s);
	while (r != 3 && (ret = read(0, &buf, 6)) && buf[0] != '\n')
	{
		if (buf[0] == 12 && ret == 1)
			break ;
		ioctl(0, TIOCGWINSZ, &sz);
		s->col = sz.ws_col;
		if (!(r = recup_stdin(&*s, buf, &i, ret)))
			return (0);
	}
	init_lst_b2(s, buf, ret);
	if (buf[0] != '\n' && r < 3)
		return (2);
	if (s->lbg)
		if (!(edit_history(&s->h, s->lbg, s->lbg, NULL)))
			return (0);
	s->nl = 0;
	return (init_lst_b3(s, &term));
}
