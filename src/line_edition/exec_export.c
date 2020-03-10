#include "../../includes/projectinclude.h"

int		checkenv_export(char **av, t_lst2 *l, int i, int c)
{
	while (av[1][c] && av[1][c] != '=')
		c++;
	while (l)
	{
		while (l->env[i] && l->env[i] != '=')
			i++;
		if (i == c)
			if (ft_strncmp(av[1], l->env, c) == 0)
			{
				l->lcl = 0;
				return (0);
			}
		l = l->next;
		i = 0;
	}
	c = 0;
	while (av[1][c])
		if (av[1][c++] == '=')
			++i;
	if (i != 1)
	{
		ft_2eputendl("setenv: bad variable declaration.\n",
		"usage: [variable environnement name]=[variable...]");
		return (1);
	}
	return (1);
}

t_lst2	*exec_export2(t_lst2 *l, char *s, int c, t_struct *st)
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

int		exec_export3(t_struct *s)
{
	t_lst2	*l;

	l = s->env;
	while (l)
	{
		if (!l->lcl && ft_strcmp(l->varn, "_"))
			ft_putendl(l->env);
		l = l->next;
	}
	return (0);
}

int		exec_export(t_struct *s, char **av)
{
	t_lst2	*l;

	if (!av[1])
		return (exec_export3(s));
	else if (av[1][0] == '=' || ft_isnum(av[1][0]))
	{
		ft_putendl("export: error: bad variable name.");
		return (1);
	}
	else if (!((*s).t = checkenv_export(av, (*s).env, 0, 0)) || (*s).t == -1)
		return (s->t);
	l = s->env;
	while (l)
		if (!ft_strcmp(av[1], l->varn) && !l->lcl)
		{
			exec_unsetenv(s, av);
			exec_setenv(s, av, NULL, 0);
			return (0);
		}
		else
			l = l->next;
	return (0);
}
