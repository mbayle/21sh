#include "minishell.h"

static int	op_copy2(t_lst **sa, t_lst **bg, char **l, int *c)
{
	*sa = *bg;
	while (*bg && (*bg)->sel)
	{
		(*c)++;
		*bg = (*bg)->next;
	}
	if ((*l = (char*)malloc(sizeof(**l) * (*c + 1))) == NULL)
		return (0);
	*c = 0;
	while (*sa != *bg)
	{
		(*l)[*c] = (*sa)->c;
		(*c)++;
		*sa = (*sa)->next;
	}
	return (1);
}

int			op_copy(t_struct *s, int i, char **l)
{
	t_lst	*bg;
	t_lst	*sa;
	int		c;

	if (*l)
		*l = NULL;
	c = 0;
	if (i > 1)
		bg = s->lbg;
	else
		bg = s->tmp;
	while (bg && !bg->sel)
		bg = bg->next;
	if (!bg)
		return (1);
	if (!(op_copy2(&sa, &bg, &*l, &c)))
		return (0);
	reset_sel(s);
	return (1);
}
