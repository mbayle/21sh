/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 23:09:45 by frameton          #+#    #+#             */
/*   Updated: 2020/02/16 02:16:50 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

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

	(*s).prompt = 1;
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

int		exec_builtin2(t_struct *s, int c)
{
	char	*ocwd;

	ocwd = NULL;
	if (c == 1)
	{
		ocwd = getcwd(ocwd, PATH_MAX);
		(*s).prompt = 1;
		exec_cd(&*s, (*s).env, NULL, ocwd);
		free(ocwd);
	}
	if (c == 2)
		if (exec_setenv(&*s) == 0)
			return (0);
	if (c == 3)
		if (exec_unsetenv(&*s) == 0)
			return (0);
	if (c == 6)
		exec_setcpt(s);
	if (c == 7)
		exec_sethelp();
	if (c == 8)
		exec_history(*s);
	return (1);
}

int		exec_builtin(t_struct *s, int c)
{
	t_lst2	*cp;
	int		i;

	cp = (*s).env;
	i = 1;
	if (c == 0)
	{
		while ((*s).av[i])
			if ((*s).av[i + 1])
				ft_2putstr((*s).av[i++], " ");
			else
				ft_putstr((*s).av[i++]);
		ft_putchar('\n');
	}
	if (c == 4)
		while (cp)
		{
			ft_putendl(cp->env);
			cp = cp->next;
		}
	if (c == 5)
		(*s).exit = 1;
	if (exec_builtin2(&*s, c) == 0)
		return (0);
	return (1);
}
