#include "minishell.h"

int			del_move(int c)
{
	while (c--)
	{
		tputs(tgetstr("le", NULL), 1, ft_ptchar);
		tputs(tgetstr("dc", NULL), 1, ft_ptchar);
	}
	return (1);
}

static int	move_cur(t_struct *s, char buf[5])
{
	if ((buf[2] == 65 || buf[2] == 70) && s->tmp)
	{
		s->lbg = s->tmp;
		while (s->tmp && s->tmp->next)
			s->tmp = s->tmp->next;
	}
	if (buf[2] == 67)
		s->lbg = s->tmp;
	return (1);
}

static	int		move_word_edl3(t_struct *s, int c)
{
	t_lst	*tp;

	if (c == 68 || c == 66 || c == 65)
		return (1);
	s->lbg = s->tmp;
	while (s->tmp->next && !(check_whitespaces((s->tmp->next->c))))
		s->tmp = s->tmp->next;
	tp = s->tmp->next;
	while (tp && check_whitespaces(tp->c))
		tp = tp->next;
	if (tp && tp != s->tmp && !(check_whitespaces(tp->c)))
		s->tmp = tp->prev;
	return (1);
}

int		edit_line3(t_struct *s, char buf[5])
{
	if (buf[0] == 27 && buf[1] == 27 && buf[2] == 91
	&& (buf[3] == 67 || buf[3] == 68 || buf[3] == 65 || buf[3] == 66))
		return (move_word_edl3(s, buf[3]));
	if ((buf[0] == 127 || (buf[0] == 27 && buf[3] == 126)))
		return (1);
	if ((buf[0] == 27 && buf[1] == 91) && (buf[2] == 68 || buf[2] == 67
				|| buf[2] == 65 || buf[2] == 66 || buf[2] == 70 || buf[2] == 72))
		return (move_cur(s, buf));
	return (0);
}
