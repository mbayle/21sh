#include "minishell.h"

int		check_input_exist2(t_struct *s, int *i, int *c)
{
	s->l = s->lbg;
	*i = 0;
	*c = 0;
	while (s->l)
	{
		if (check_whitespaces(s->l->c))
			return (2);
		(*c)++;
		s->l = s->l->next;
	}
	return (1);
}

int		check_input_exist3(t_struct s, int c, int i, t_htr *com)
{
	char	line[c + 1];
	int		j;

	j = 0;
	s.l = s.lbg;
	while (s.l && j < c)
	{
		line[j]= s.l->c;
		s.l = s.l->next;
		j++;
	}
	line[j] = '\0';
	while (*s.builtin_ref)
	{
		if (!ft_strcmp(line, *s.builtin_ref))
			return (1);
		s.builtin_ref++;
	}
	while (com)
	{
		if (!(ft_strcmp(line, com->name)))
			i = 1;
		com = com->next;
	}
	return (i);
}

int		check_input_exist(t_struct s, t_htr *com)
{
	int		c;
	int		i;
	int		d;

	d = check_input_exist2(&s, &i, &c);
	if (d == 2 && s.cki)
		return (1);
	i = check_input_exist3(s, c, i, com);
	if (i)
		return (1);
	return (0);
}
