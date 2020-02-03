#include "minishell.h"

static void	recup_stdin2(int *c, t_struct *s, int *i, t_htr **t)
{
	if (!(*c = 0) && !(s->lbg))
	{
		if (!(s->tmp))
			*i = 0;
		*t = NULL;
	}
}

int			recup_stdin(t_struct *s, char buf[5], int *i, int ret)
{
	int				c;
	int				r;
	static t_htr	*t;

	recup_stdin2(&c, s, &*i, &t);
	r = 2;
	if (s->comp.name && !(init_lst_comp(buf, &*s, NULL, NULL)))
		return (0);
	while (r == 2 && c < ret)
	{
		if (!s->lbg && s->tmp)
			r = init_lst_4(s, buf, c);
		else if (!s->tmp || !s->tmp->next)
			r = init_lst_2(&*s, buf, &*i, &t, c);
		else if (s->lbg && s->tmp && s->tmp->next)
			r = init_lst_3(&*s, buf, c, NULL);
		c++;
		write_lst(s, buf, &s->nl);
		s->set_cpt = 0;
	}
	if (r != 3)
		r = 2;
	if (r == -1)
		return (0);
	return (r);
}
