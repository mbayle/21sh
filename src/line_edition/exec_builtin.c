/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 23:09:45 by frameton          #+#    #+#             */
/*   Updated: 2020/03/09 05:34:41 by frameton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

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
		if (exec_setenv(&*s, NULL) == 0)
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
