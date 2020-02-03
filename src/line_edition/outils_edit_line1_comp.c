#include "minishell.h"

static	void	show_list_poss3(t_comp **cmp, int *i, int *co, t_comp **bcmp)
{
	while (*cmp)
	{
		if ((int)ft_strlen((*cmp)->name) > *i)
			*i = ft_strlen((*cmp)->name);
		*cmp = (*cmp)->next;
	}
	*cmp = *bcmp;
	*co = (*co / (*i + 3));
	*cmp = attribute_col(&*co, *cmp);
	*cmp = *bcmp;
}

static int		show_list_poss2(t_struct *s, t_comp **cmp, int row,  int *co)
{
	int             i;
	int             j;
	int             size;
	t_comp  *bcmp;

	i = 0;
	j = 0;
	size = 0;
	bcmp = *cmp;
	show_list_poss3(&*cmp, &i, &*co, &bcmp);
	print_comp_tab(*cmp, 0, i, &j);
	*cmp = bcmp;
	while (*cmp)
	{
		if ((*cmp)->col == 1)
			++size;
		*cmp = (*cmp)->next;
	}
	if (size > row - 1)
		return (1);
	fp("vi", NULL);
	if (!(select_comp_tab(s, bcmp, i, j)))
		return (-1);
	fp("ve", NULL);
	return (1);
}

int				show_list_poss(t_struct *s)
{
	t_comp	*cmp;
	t_comp	*bcmp;
	int		co;
	int		j;
	int		row;

	j = 0;
	cmp = NULL;
	bcmp = NULL;
	if (!(row = init_list_poss(s, &co, &cmp, &bcmp)))
		return (0);
	if (no_match(*s, bcmp))
		return (1);
	if (!bcmp->next)
	{
		free(bcmp);
		return (1);
	}
	if (cmp)
		ft_putchar('\n');
	tputs(tgetstr("sc", NULL), 1, ft_ptchar);
	cmp = bcmp;
	return (show_list_poss2(s, &cmp, row, &co));
}
