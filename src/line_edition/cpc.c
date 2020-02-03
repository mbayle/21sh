#include "minishell.h"

void	reset_sel(t_struct *s)
{
	t_lst	*r;

	if (!s->lbg)
		r = s->tmp;
	else
		r = s->lbg;
	while (r)
	{
		r->sel = 0;
		r = r->next;
	}
}

int		free_sel(t_lst **bg, t_lst **end)
{
	t_lst	*del;

	while (*bg != *end)
	{
		del = *bg;
		*bg = (*bg)->next;
		free(del);
	}
	return (1);
}

int		create_char(t_lst **end, char c)
{
	t_lst	*new;

	if ((new = malloc(sizeof(*new))) == NULL)
		return (0);
	new->next = NULL;
	new->c = c;
	new->sel = 0;
	new->prev = *end;
	new->plc = 0;
	new->line = 0;
	(*end)->next = new;
	*end = (*end)->next;
	return (1);
}

int		cpc(t_struct *s, char b, int i)
{
	static char	*l;

	if (i == 3 && !s->lbg && b != -128)
		return (1);
	if (b == -120)
		if (!op_copy(s, i, &l))
			return (0);
	if (b == -82)
		op_cut(s, i);
	if (b == -128)
		op_paste(s, &l);
	return (1);
}
