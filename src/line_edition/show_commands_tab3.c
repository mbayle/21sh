#include "projectinclude.h"

static int	s_command3_tab2(t_comp **l, t_comp **bg, char *str)
{
	if ((*l = malloc(sizeof(**l))) == NULL)
		return (0);
	if (((*l)->name = ft_mstrcpy((*l)->name, str)) == NULL)
		return (0);
	(*l)->next = NULL;
	(*l)->prev = NULL;
	(*l)->col = 0;
	(*l)->sel = 0;
	*bg = *l;
	return (1);
}

int			s_command_tab2(char *str, t_comp **l, t_comp **bg,
		char *p)
{
	if (!*l)
	{
		if (!(s_command3_tab2(&*l, &*bg, str)))
			return (0);
	}
	else
	{
		if (((*l)->next = malloc(sizeof(**l))) == NULL)
			return (0);
		if (((*l)->next->name = ft_mstrcpy((*l)->next->name
						, str)) == NULL)
			return (0);
		(*l)->next->next = NULL;
		(*l)->next->prev = *l;
		(*l)->col = 0;
		(*l)->sel = 0;
		*l = (*l)->next;
	}
	(*l)->clr = clr_cmp(*l, p);
	return (1);
}
