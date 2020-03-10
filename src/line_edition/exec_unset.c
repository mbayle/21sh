/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frameton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 18:47:26 by frameton          #+#    #+#             */
/*   Updated: 2020/03/10 18:47:28 by frameton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

int		checkenv_unset(char **av, t_lst2 *l)
{
	int		c;
	int		lc;
	int		i;

	c = 0;
	i = 0;
	lc = 0;
	while (av[1][c] && av[1][c] != '=')
		c++;
	while (l)
	{
		++lc;
		while (l->env[i] && l->env[i] != '=')
			i++;
		if (i == c)
		{
			if (ft_strncmp(av[1], l->varn, c) == 0 && l->lcl)
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

int		exec_unset(t_struct *s, char **av)
{
	t_lst2	*new;
	t_lst2	*cp;
	int		c;

	new = (*s).env;
	cp = (*s).env;
	if (!av[1])
		ft_putendl("unset: error: no variable indicated.");
	else if (av[1][0] == '=')
		ft_putendl("unset: error: bad variable name.");
	else if ((c = checkenv_unset(av, (*s).env)) == -1)
		return (1);
	else
		exec_unset2(&*s, &new, &cp, c);
	return (0);
}
