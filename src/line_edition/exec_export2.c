/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 23:01:08 by frameton          #+#    #+#             */
/*   Updated: 2020/03/10 02:52:38 by frameton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

static int	exec_export4b(t_struct *s, char ***tmp, t_lst2 **l)
{
	char	*tm;

	tm = ft_strdup((*l)->varn);
	exec_setenv(s, *tmp, NULL, 0);
	*l = s->env;
	while (*l)
	{
		if (!ft_strcmp(tm, (*l)->varn))
			(*l)->lcl = 0;
		*l = (*l)->next;
	}
	free(tm);
	free_tmp_export5(&*tmp);
	return (0);
}

int			exec_export4(t_struct *s, int c, char **av, int i)
{
	char	**tmp;
	t_lst2	*l;

	l = NULL;
	if (!(exec_export5(&tmp, av, s, &l)))
		return (0);
	while (l)
		if (!ft_strncmp(av[i], l->varn, c))
		{
			return (exec_export4b(s, &tmp, &l));
		}
		else
			l = l->next;
	free_tmp_export5(&tmp);
	return (exec_setenv_b(s, av, i, 1));
}
