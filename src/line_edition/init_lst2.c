#include "minishell.h"

static void	init_lst_2b(t_struct *s, int *i, t_lst **l, t_htr **t)
{
	if (!*i && !*t)
	{
		(*l)->prev = NULL;
		s->lbg = *l;
		s->tmp = *l;
		*i = 1;
	}
	else
	{
		(*l)->prev = s->tmp;
		s->tmp->next = *l;
		s->tmp = s->tmp->next;
	}
	if (s->comp.name)
	{
		ft_putchar((*l)->c);
		s->comp.name = NULL;
	}
}

static int	init_lst_2_b(t_struct *s, char buf[5])
{
	if (!s->lbg && !s->tmp)
		return (1);
	if (!s->tmp->sel)
		s->tmp->sel = 1;
	else
		s->tmp->sel = 0;
	if (buf[5] == 68)
		if (s->tmp->prev)
			s->tmp = s->tmp->prev;
	if (buf[5] == 67)
		if (s->tmp->next)
			s->tmp = s->tmp->next;
	return (1);
}

static int	init_lst_2_b2(t_struct *s, char buf[5])
{
	if (buf[2] == 81)
	{
		if (s->cpt < 5)
			s->cpt++;
		else
			tputs(tgetstr("bl", NULL), 1, ft_ptchar);
	}
	else
	{
		if (s->cpt > 1)
			s->cpt--;
		else
			tputs(tgetstr("bl", NULL), 1, ft_ptchar);
	}
	s->set_cpt = 1;
	return (1);
}

static int	init_lst_2_b3(t_struct *s, char buf[5])
{
	if ((buf[0] == 127 || (buf[0] == 27 && buf[3] == 126)) && (s->cpt > 3))
		return (ft_completion(&*s, NULL, buf, 2));
	return (ft_completion(&*s, NULL, buf, 0));
}

int			init_lst_2(t_struct *s, char buf[5], int *i, t_htr **t, int c)
{
	t_lst	*l;

	l = NULL;
	if (edit_line(&*s, buf, &*i, &*t))
		return (init_lst_2_b3(s, buf));
	if ((buf[0] == -49 && buf[1] == -128)
			|| (buf[0] == -62 && buf[1] == -82)
			|| (buf[0] == -30 && buf[1] == -120 && buf[2] == -126))
		return (cpc(s, buf[1], 3));
	if (buf[0] == 18 && !s->lbg)
		return (ctrl_r(s));
	if (buf[0] == 27 && buf[1] == 91 && buf[2] == 49 && buf[3] == 59
			&& buf[4] == 50)
		return (init_lst_2_b(s, buf));
	if (buf[0] == 27 && buf[1] == 79 && (buf[2] == 80 || buf[2] == 81))
		return (init_lst_2_b2(s, buf));
	if ((l = malloc(sizeof(*l))) == NULL)
		return (-1);
	l->c = buf[c];
	l->sel = 0;
	l->next = NULL;
	init_lst_2b(&*s, &*i, &l, &*t);
	if ((ft_completion(&*s, NULL, buf, 0)) == 1)
		return (2);
	return (2);
}
