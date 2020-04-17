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
	while (av[i][c] && av[i][c] != '=')
		c++;
	if (av[i][c])
		return (1);
	c = 0;
	while (l)
	{
		if (ft_strcmp(av[i], l->varn) == 0)
		{
			l->lcl = 0;
			return (0);
		}
		l = l->next;
	}
	if (!l)
	{
		ft_eputstr("export: "RED);
		ft_eputstr(av[i]);
		ft_eputendl(WHITE": variable not found.\n");
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
		if ((l->var = ft_strdup(s)) == NULL)
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

int		exec_export4(t_struct *s, int c, char **av, int i)
{
	char	**tmp;
	char	*tm;
	t_lst2	*l;

	l = NULL;
	if (!(exec_export5(&tmp, av, s, &l)))
		return (0);
	while (l)
		if (!ft_strncmp(av[i], l->varn, c))
		{
			tm = ft_strdup(l->varn);
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
	return (exec_setenv_b(s, av, i, 1));
}

int		exec_export_b(t_struct *s, char **av, int i)
{
	int		c;

	c = 0;
	if (!av[i])
		return (exec_export3(s));
	else if (av[i][0] == '=' || ft_isnum(av[i][0]))
	{
		ft_eputstr("export: "RED);
		ft_eputstr(av[i]);
		ft_eputendl(WHITE": bad variable name.");
		return (1);
	}
	else if (!((*s).t = checkenv_export(av, (*s).env, i, 0)) || (*s).t == -1)
	{
		if ((*s).t == -1)
			return (1);
		return (s->t);
	}
	while (av[i][c] != '=')
		++c;
	return (exec_export4(s, c, av, i));
}

int		exec_export(t_struct *s, char **av)
{
	int		c;
	int		i;

	c = 1;
	i = 0;
	if (!av[1])
	{
		ft_putendl("export: error: no variable indicated.");
		return (1);
	}
	while (av[c])
	{
		if (exec_export_b(s, av, c))
			i = 1;
		++c;
	}
	return (i);
}
