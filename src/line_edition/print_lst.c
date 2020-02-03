#include "minishell.h"

static t_lst	*print_lst2(t_struct s, int *c, int *i, int *nl)
{
	s.l = s.lbg;
	while (s.l)
	{
		if (s.l->sel)
			ft_putstr(BWHITE);
		write(1, &s.l->c, 1);
		ft_putstr(WHITE);
		*c = s.l->plc;
		if (s.l->plc == *i)
		{
			ft_putchar('\n');
			(*nl)++;
			*i = *i + s.col;
		}
		s.l = s.l->next;
	}
	return (s.l);
}

int				print_lst(t_struct s, int *nl, int c)
{
	int		i;

	i = s.col;
	*nl = 0;
	tputs(tgetstr("dl", NULL), 1, ft_ptchar);
	s.cki = check_input_exist(s, s.bcom);
	if (s.cki && s.cpt > 1)
		print_prompt_bis(s.prompt, &s, 1);
	else
		print_prompt_bis(s.prompt, &s, 0);
	s.l = print_lst2(s, &c, &i, &*nl);
	while (s.comp.name && s.comp.sz--)
	{
		++c;
		if (c == i)
		{
			ft_putchar('\n');
			(*nl)++;
			i = i + s.col;
		}
		ft_putstr(BCYAN);
		ft_putchar(*s.comp.name++);
		ft_putstr(WHITE);
	}
	return (s.cki);
}
