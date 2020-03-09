#include "../../includes/projectinclude.h"

int		checkenv_unset(t_struct s, t_lst2 *l)
{
	int		c;
	int		lc;
	int		i;

	c = 0;
	i = 0;
	lc = 0;
	while (s.av[1][c] && s.av[1][c] != '=')
		c++;
	while (l)
	{
		++lc;
		while (l->env[i] && l->env[i] != '=')
			i++;
		if (i == c)
		{
			if (ft_strncmp(s.av[1], l->env, c) == 0 && l->lcl)
				return (lc);
		}
		l = l->next;
		i = 0;
	}
	return (-1);
}

void	exec_unset2(t_struct *s, t_lst2 **new, t_lst2 **cp, int c)
{
	if (c == 1)
	{
		(*s).env = (*cp)->next;
		free((*cp)->env);
		if ((*cp)->var)
			free((*cp)->var);
		if ((*cp)->nvar)
			free((*cp)->varn);
		free(*cp);
	}
	else
	{
		c--;
		while (--c)
			*new = (*new)->next;
		*cp = (*new)->next;
		(*new)->next = (*cp)->next;
		free((*cp)->env);
		if ((*cp)->var)
			free((*cp)->var);
		if ((*cp)->nvar)
			free((*cp)->varn);
		free(*cp);
	}
}

int		exec_unset(t_struct *s)
{
	t_lst2	*new;
	t_lst2	*cp;
	int		c;

	new = (*s).env;
	cp = (*s).env;
	if ((s->av = ft_splitws(s->cmd)) == NULL)
		return (1);
	if (!(*s).av[1])
		ft_putendl("unset: error: no variable indicated.");
	else if ((*s).av[1][0] == '=')
		ft_putendl("unset: error: bad variable name.");
	else if ((c = checkenv_unset(*s, (*s).env)) == -1)
		return (1);
	else
		exec_unset2(&*s, &new, &cp, c);
	return (0);
}
