#include "minishell.h"

void	es9(char *s, int m)
{
	ft_mputendl(s, m);
}

int		exec_setcpt8(t_struct *s, struct termios *term, int *m)
{
	struct winsize	sz;
	int				mh;

	(void)*s;
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

void	exec_setcpt6(t_struct *s, int m)
{
	int		ret;

	exec_setcpt2(s, m);
	exec_setcpt3(s, m);
	ft_putchar('\n');
	ret = 23;
	while (ret--)
	{
		tputs(tgetstr("up", NULL), 1, ft_ptchar);
		tputs(tgetstr("dl", NULL), 1, ft_ptchar);
	}
	tputs(tgetstr("cl", NULL), 1, ft_ptchar);
	ft_putstr(WHITE"Level completion "GREEN);
	ft_putnbr(s->cpt);
	ft_putendl(WHITE" is set"WHITE);
}

void	exec_setcpt7(t_struct *s)
{
	if (s->cpt == 5)
	{
		tputs(tgetstr("le", NULL), 1, ft_ptchar);
		tputs(tgetstr("sc", NULL), 1, ft_ptchar);
		tputs(tgetstr("nd", NULL), 1, ft_ptchar);
		tputs(tgetstr("nd", NULL), 1, ft_ptchar);
		tputs(tgetstr("nd", NULL), 1, ft_ptchar);
		ft_putstr(WHITE" "MAGENTA);
		tputs(tgetstr("rc", NULL), 1, ft_ptchar);
		tputs(tgetstr("nd", NULL), 1, ft_ptchar);
	}
	if (s->cpt == 1)
	{
		tputs(tgetstr("le", NULL), 1, ft_ptchar);
		tputs(tgetstr("sc", NULL), 1, ft_ptchar);
		tputs(tgetstr("le", NULL), 1, ft_ptchar);
		tputs(tgetstr("le", NULL), 1, ft_ptchar);
		tputs(tgetstr("le", NULL), 1, ft_ptchar);
		ft_putstr(WHITE" "MAGENTA);
		tputs(tgetstr("rc", NULL), 1, ft_ptchar);
		tputs(tgetstr("nd", NULL), 1, ft_ptchar);
	}
}
