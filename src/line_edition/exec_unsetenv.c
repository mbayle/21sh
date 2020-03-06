/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_unsetenv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 23:00:21 by frameton          #+#    #+#             */
/*   Updated: 2020/02/16 02:16:50 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

static int	checkenv_unsetenv(t_struct s, t_lst2 *l)
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
			if (ft_strncmp(s.av[1], l->env, c) == 0)
				return (lc);
		}
		l = l->next;
		i = 0;
	}
	return (-1);
}

static void	exec_unsetenv2(t_struct *s, t_lst2 **new, t_lst2 **cp, int c)
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

int			exec_unsetenv(t_struct *s)
{
	t_lst2	*new;
	t_lst2	*cp;
	int		c;

	new = (*s).env;
	cp = (*s).env;
	if (!(*s).av[1])
	{
		ft_putendl("setenv: error: no variable indicated.");
		(*s).prompt = 1;
	}
	else if ((*s).av[1][0] == '=')
	{
		ft_putendl("setenv: error: bad variable name.");
		(*s).prompt = 1;
	}
	else if ((c = checkenv_unsetenv(*s, (*s).env)) == -1)
		(*s).prompt = 1;
	else
		exec_unsetenv2(&*s, &new, &cp, c);
	return (1);
}
