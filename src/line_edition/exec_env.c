/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frameton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 18:48:08 by frameton          #+#    #+#             */
/*   Updated: 2020/03/11 20:19:18 by frameton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

int		exec_env(t_struct *s)
{
	t_lst2		*l;

	l = s->env;
	while (l)
	{
		if (!l->lcl)
			ft_putendl(l->env);
		l = l->next;
	}
	return (0);
}
