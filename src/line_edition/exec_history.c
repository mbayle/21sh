/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frameton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 23:52:36 by frameton          #+#    #+#             */
/*   Updated: 2020/02/03 23:54:28 by frameton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		exec_history(t_struct s)
{
	t_htr	*tmp;
	int		c;

	c = 1;
	if (!s.h)
	{
		ft_putendl(RED"No commands found."WHITE);
		return (1);
	}
	tmp = s.h;
	while (tmp->next)
		tmp = tmp->next;
	ft_putchar('\n');
	while (tmp)
	{
		ft_putnbr(c++);
		ft_2putstr("  ", tmp->name);
		ft_putchar('\n');
		tmp = tmp->prev;
	}
	ft_putchar('\n');
	return (1);
}
