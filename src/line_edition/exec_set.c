/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_set.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frameton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 04:25:07 by frameton          #+#    #+#             */
/*   Updated: 2020/03/10 03:02:39 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

int		exec_set(t_struct *s, char **av)
{
	t_lst2	*l;

	(void)av;
	if ((s->av = ft_splitws(s->cmd)) == NULL)
		return (1);
	if ((*s).av[1])
		return (0);
	l = s->env;
	while (l)
	{
		ft_putendl(l->env);
		l = l->next;
	}
	return (0);
}
