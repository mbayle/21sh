#include "../../includes/projectinclude.h"

int		checkenv_setenv(t_struct s, t_lst2 *l, int i, int c)
{
	while (s.av[1][c] && s.av[1][c] != '=')
		c++;
	while (l)
	{
		while (l->env[i] && l->env[i] != '=')
			i++;
		if (i == c)
			if (ft_strncmp(s.av[1], l->env, c) == 0)
				return (0);
		l = l->next;
		i = 0;
	}
	c = 0;
	while (s.av[1][c])
		if (s.av[1][c++] == '=')
			++i;
	if (i != 1)
	{
		ft_2eputendl("setenv: bad variable declaration.\n",
		"usage: [variable environnement name]=[variable...]");
		return (-1);
	}
	return (1);
}

t_lst2	*exec_setenv2(t_lst2 *l, char *s, int c, t_struct *st)
{
	t_lst2	*cp;

	cp = (*st).env;
	while (cp && cp->next)
		cp = cp->next;
	while (s[c] && s[c] != '=')
		++c;
	if ((l->varn = (char*)malloc(sizeof(*l->varn) * (c + 1))) == NULL)
		return (NULL);
	c = 0;
	while (*s && *s != '=' && (l->varn[c++] = *s))
		s++;
	l->varn[c] = '\0';
	s++;
	l->var = NULL;
	if ((l->nenv = ft_strlen(s)))
		if ((l->var = ft_mstrcpy(l->var, s)) == NULL)
			return (NULL);
	l->size = ft_strlen(l->env);
	l->nvar = ft_strlen(l->varn);
	l->next = NULL;
	if (cp)
		cp->next = l;
	return (l);
}

int		exec_setenv(t_struct *s)
{
	t_lst2	*new;

	s->av = ft_split_whitespaces(s->cmd);
	(*s).prompt = 1;
	puts("1");
	if (!(*s).av[1])
		ft_putendl("setenv: error: no variable indicated.");
	else if ((*s).av[1][0] == '=')
		ft_putendl("setenv: error: bad variable name.");
	else if (!((*s).t = checkenv_setenv(*s, (*s).env, 0, 0)) || (*s).t == -1)
	{
		if ((*s).t == 0)
			ft_putendl("setenv: error: the specified variable already exists.");
	}
	else
	{
		puts("3");
		if ((new = malloc(sizeof(*new))) == NULL)
			return (0);
		if ((new->env = ft_mstrcpy(new->env, (*s).av[1])) == NULL)
			return (0);
		if ((new = exec_setenv2(new, (*s).av[1], 0, &*s)) == NULL)
			return (0);
		if (!(*s).env)
			(*s).env = new;
		(*s).prompt = 0;
	}
	return (1);
}
