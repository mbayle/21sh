/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frameton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 18:48:00 by frameton          #+#    #+#             */
/*   Updated: 2020/03/10 19:15:40 by frameton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

int		checkenv_export(char **av, t_lst2 *l, int i, int c)
{
	(void)i;
	while (av[1][c] && av[1][c] != '=')
		c++;
	if (av[1][c])
		return (1);
	c = 0;
	while (l)
	{
		if (ft_strcmp(av[1], l->varn) == 0)
		{
			l->lcl = 0;
			return (0);
		}
		l = l->next;
	}
	if (!l)
	{
		ft_eputendl("setenv: variable not found.\n");
		return (-1);
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

int		exec_export4(t_struct *s, int c, char **av, t_lst2 *l)
{
	char	**tmp;
	char	*tm;

	if (!(exec_export5(&tmp, av, s, &l)))
		return (0);
	while (l)
		if (!ft_strncmp(av[1], l->varn, c))
		{
			tm = ft_mstrcpy(NULL, l->varn);
			exec_setenv(s, tmp, NULL, 0);
			l = s->env;
			while (l)
			{
				if (!ft_strcmp(tm, l->varn))
					l->lcl = 0;
				l = l->next;
			}
			free(tm);
			free_tmp_export5(&tmp);
			return (0);
		}
		else
			l = l->next;
	free_tmp_export5(&tmp);
	return (exec_setenv(s, av, NULL, 1));
}

int		exec_export(t_struct *s, char **av)
{
	int		c;

	c = 0;
	if (!av[1])
		return (exec_export3(s));
	else if (av[1][0] == '=' || ft_isnum(av[1][0]))
	{
		ft_putendl("export: error: bad variable name.");
		return (1);
	}
	else if (!((*s).t = checkenv_export(av, (*s).env, 0, 0)) || (*s).t == -1)
	{
		if ((*s).t == -1)
			return (1);
		return (s->t);
	}
	while (av[1][c] != '=')
		++c;
	return (exec_export4(s, c, av, NULL));
}
