/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_setenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frameton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 18:47:35 by frameton          #+#    #+#             */
/*   Updated: 2020/03/12 13:51:03 by frameton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

int		checkenv_setenv(char **av, t_lst2 **l, int j, int c)
{
	int		i;

	while (!(i = 0) && av[j][c] && av[j][c] != '=')
		c++;
	while (*l)
	{
		while ((*l)->env[i] && (*l)->env[i] != '=')
			i++;
		if (i == c)
			if (ft_strncmp(av[j], (*l)->env, c) == 0)
				return (0);
		*l = (*l)->next;
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
	l->lcl = 0;
	l->size = ft_strlen(l->env);
	l->nvar = ft_strlen(l->varn);
	l->next = NULL;
	if (cp)
		cp->next = l;
	return (l);
}

int		exec_setenv3(char **av, t_struct *s, t_lst2 *l, int c)
{
	if (s->t == 0)
	{
		if (l->lcl == 0)
			exec_unsetenv_b(s, av, c);
		else if (l && l->lcl == 1)
			exec_unset_b(s, av, c);
		exec_setenv_b(s, av, c, g_jobcontrol.s.i);
		return (0);
	}
	return (1);
}

int		exec_setenv_b(t_struct *s, char **av, int c, int i)
{
	t_lst2	*l;
	t_lst2	*new;

	new = NULL;
	l = (*s).env;
	if (av[c][0] == '=')
	{
		ft_eputstr("setenv: "RED);
		ft_eputstr(av[c]);
		ft_eputendl(WHITE": bad variable name.");
		return (1);
	}
	else if (!((*s).t = checkenv_setenv(av, &l, c, 0)) || (*s).t == -1)
		return (exec_setenv3(av, s, l, c));
	else
	{
		if ((new = malloc(sizeof(*new))) == NULL)
			return (1);
		if ((new->env = ft_mstrcpy(new->env, av[c])) == NULL)
			return (1);
		if ((new = exec_setenv2(new, av[c], 0, &*s)) == NULL)
			return (1);
		if (i == 0)
			new->lcl = 1;
		if (!(*s).env)
			(*s).env = new;
		if (!ft_strcmp(new->varn, "PATH"))
			hash_reset(&g_jobcontrol.h_tab);
	}
	return (0);
}

int		exec_setenv(t_struct *s, char **av, t_lst2 *new, int i)
{
	int		c;

	(void)new;
	c = i;
	if (!av[1] && i)
	{
		ft_eputendl("setenv: error: no variable indicated.");
		return (1);
	}
	g_jobcontrol.s.i = 0;
	if (i)
		g_jobcontrol.s.i = 1;
	while (av[c])
	{
		exec_setenv_b(s, av, c, i);
		++c;
	}
	return (1);
}
