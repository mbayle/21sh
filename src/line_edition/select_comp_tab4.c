/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_comp_tab4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frameton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 00:23:51 by frameton          #+#    #+#             */
/*   Updated: 2020/01/25 00:23:52 by frameton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	down_touch2(t_comp **cmp, t_comp *bcmp, int c)
{
	while ((*cmp)->col != c)
	{
		*cmp = (*cmp)->next;
		if (!*cmp && ((*cmp) = bcmp))
			*cmp = bcmp;
	}
	(*cmp)->sel = 1;
}

void	down_touch(t_comp *cmp, t_comp *bcmp, int *j, int i)
{
	int		c;

	while (!cmp->sel)
		cmp = cmp->next;
	cmp->sel = 0;
	c = cmp->col;
	if (cmp->next)
		cmp = cmp->next;
	else
		cmp = bcmp;
	down_touch2(&cmp, bcmp, c);
	c = 0;
	while (c < *j)
	{
		tputs(tgetstr("up", NULL), 1, ft_ptchar);
		tputs(tgetstr("dl", NULL), 1, ft_ptchar);
		++c;
	}
	del_move(4);
	*j = 0;
	print_comp_tab(bcmp, 0, i, &*j);
}
