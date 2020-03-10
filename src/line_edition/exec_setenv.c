#include "../../includes/projectinclude.h"

int		checkenv_setenv(char **av, t_lst2 *l, int j, int c)
{
	int		i;

	while (!(i = 0) && av[j][c] && av[j][c] != '=')
		c++;
	while (l)
	{
		while (l->env[i] && l->env[i] != '=')
			i++;
		if (i == c)
			if (ft_strncmp(av[j], l->env, c) == 0)
				return (0);
		l = l->next;
		i = 0;
	}
	c = 0;
	while (av[j][c])
		if (av[j][c++] == '=')
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
	l->lcl = 1;
	l->size = ft_strlen(l->env);
	l->nvar = ft_strlen(l->varn);
	l->next = NULL;
	if (cp)
		cp->next = l;
	return (l);
}

int		exec_setenv3(char **av, t_struct *s, int e)
{
	int		i;
	char	**tmp;
	char	**dst;

	i = -1;
	if (!(dst = malloc(sizeof(char*) * (tab_size(av)+ 1))))
		return (-1);
	while (av[++i])
	{
		tmp = ft_strsplit(av[i], '=');
		dst[i] = ft_strdup(tmp[0]);
		ft_freetab(tmp);
	}
	dst[i] = NULL;
	if (s->t == 0)
	{
		e == 0 ? exec_unset(s, dst) : exec_unsetenv(s, av);
		ft_putendl(dst[0]);
		ft_putnbr(e);
		return(0);
		exec_setenv(s, av, NULL, e);
		return (0);
	}
	return (1);
}

int		exec_setenv(t_struct *s, char **av, t_lst2 *new, int i)
{
	if (!av[i])
		ft_putendl("setenv: error: no variable indicated.");
	else if (av[i][0] == '=')
		ft_putendl("setenv: error: bad variable name.");
	else if (!((*s).t = checkenv_setenv(av, (*s).env, i, 0)) || (*s).t == -1)
			return (exec_setenv3(av, s, i));
	else
	{
		if ((new = malloc(sizeof(*new))) == NULL)
			return (1);
		if ((new->env = ft_mstrcpy(new->env, av[i])) == NULL)
			return (1);
		if ((new = exec_setenv2(new, av[i], 0, &*s)) == NULL)
			return (1);
		if (i == 1)
			new->lcl = 0;
		if (!(*s).env)
			(*s).env = new;
	}
	return (0);
}
