#include "minishell.h"

static int	op_cut2(t_struct *s, t_lst **end, t_lst **bg, int lbg)
{
	*end = *bg;
	while (*end && (*end)->sel)
		*end = (*end)->next;
	if (!*end)
	{
		s->tmp = NULL;
		if (lbg)
			s->lbg = NULL;
		return (free_sel(&*bg, &*end));
	}
	(*end)->prev = NULL;
	if (lbg)
	{
		s->lbg = *end;
		s->tmp = s->lbg;
	}
	else
		s->tmp = *end;
	return (free_sel(&*bg, &*end));
}

static int	op_cut3(t_lst **bg, t_lst **end, t_struct *s, int lbg)
{
	while (*bg && (*bg)->next && !(*bg)->next->sel)
		*bg = (*bg)->next;
	if (!(*bg)->next)
		return (1);
	*end = (*bg)->next;
	while (*end && (*end)->sel)
		*end = (*end)->next;
	if (!*end)
	{
		(*bg)->next = NULL;
		if (lbg)
			s->tmp = s->lbg;
		return (free_sel(&(*bg)->next, &*end));
	}
	free_sel(&(*bg)->next, &(*end)->prev);
	(*bg)->next = *end;
	(*end)->prev = *bg;
	if (lbg)
		s->tmp = s->lbg;
	return (0);
}

int			op_cut(t_struct *s, int i)
{
	t_lst	*bg;
	t_lst	*end;
	int		lbg;

	if (i == 1 && !(lbg = 0))
		bg = s->tmp;
	if (i > 1 && (lbg = 1))
		bg = s->lbg;
	if (bg->sel)
		return (op_cut2(s, &end, &bg, lbg));
	return (op_cut3(&bg, &end, s, lbg));
}
