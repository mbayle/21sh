/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_set.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frameton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 04:25:07 by frameton          #+#    #+#             */
/*   Updated: 2020/03/10 17:17:58 by frameton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

int		exec_set(t_struct *s, char **av)
{
	t_lst2	*l;

	if (av[1])
		return (0);
	l = s->env;
	while (l)
	{
		ft_putendl(l->env);
		l = l->next;
	}
	return (0);
}
