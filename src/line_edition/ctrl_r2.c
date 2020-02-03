#include "minishell.h"

t_htr	*check_htr(t_htr *t, char *l)
{
	int		c;
	char	*s;

	c = 0;
	while (t)
	{
		s = t->name;
		while (*s)
		{
			if (!(ft_strncmp(s, l, ft_strlen(l))))
				return (t);
			s++;
		}
		t = t->next;
	}
	return (t);
}

char	*new_l(char *l)
{
	char	*new;
	char	*bg;
	char	*del;
	int		c;

	c = ft_strlen(l) - 1;
	if (!c)
		return (NULL);
	del = l;
	if ((new = (char*)malloc(sizeof(*new) * (ft_strlen(l)))) == NULL)
		return (NULL);
	bg = new;
	while (c--)
	{
		*new = *l;
		new++;
		l++;
	}
	*new = '\0';
	free(del);
	return (bg);
}

int		change_lst(t_struct *s, t_htr *t, int c)
{
	s->lbg = NULL;
	s->tmp = NULL;
	if ((s->lbg = malloc(sizeof(*s->lbg))) == NULL)
		return (0);
	s->lbg->c = t->name[c++];
	s->lbg->sel = 0;
	s->lbg->plc = 0;
	s->lbg->line = 0;
	s->lbg->prev = NULL;
	s->lbg->next = NULL;
	s->tmp = s->lbg;
	ft_putendl(t->name);
	while (t->name[c])
	{
		if ((s->tmp->next = malloc(sizeof(*s->tmp))) == NULL)
			return (0);
		s->tmp->next->sel = 0;
		s->tmp->next->plc = 0;
		s->tmp->next->line = 0;
		s->tmp->next->next = NULL;
		s->tmp->next->prev = s->tmp;
		s->tmp->next->c = t->name[c++];
		s->tmp = s->tmp->next;
	}
	return (1);
}
