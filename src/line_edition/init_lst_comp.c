#include "minishell.h"

static int	init_lst_comp2(t_struct *s, t_lst **l)
{
	while (*s->comp.name)
	{
		if ((*l = malloc(sizeof(**l))) == NULL)
			return (0);
		(*l)->c = *s->comp.name;
		(*l)->prev = s->tmp;
		(*l)->sel = 0;
		(*l)->plc = 0;
		(*l)->line = 0;
		s->tmp->next = *l;
		(*l)->next = NULL;
		s->tmp = *l;
		*l = NULL;
		s->comp.name++;
	}
	return (1);
}

int			init_lst_comp(char buf[5], t_struct *s, t_lst *l, t_lst *rt)
{
	if (buf[0] == 9)
	{
		if (!(init_lst_comp2(&*s, &l)))
			return (0);
	}
	rt = s->tmp;
	while (rt)
		rt = rt->prev;
	return (1);
}
