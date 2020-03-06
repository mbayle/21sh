/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_comp_tab2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 00:24:02 by frameton          #+#    #+#             */
/*   Updated: 2020/02/16 02:16:50 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

void	left_touch2(t_comp *end, int c, int *j, t_comp **cmp)
{
	t_comp	*r;

	r = *cmp;
	while (r->col != c)
	{
		r = r->prev;
		if (!r)
			r = end;
	}
	*cmp = r;
	r->sel = 1;
	c = 0;
	while (c < *j)
	{
		fp("up", "dl");
		++c;
	}
	del_move(4);
	*j = 0;
}

void	left_touch(t_comp *cmp, t_comp *bcmp, int *j, int i)
{
	int		c;
	int		ind;
	t_comp	*end;

	while (cmp)
	{
		if (cmp->next && cmp->next->col < cmp->col)
			ind = cmp->col;
		if (!cmp->next)
			end = cmp;
		cmp = cmp->next;
	}
	cmp = bcmp;
	while (!cmp->sel)
		cmp = cmp->next;
	cmp->sel = 0;
	if (!cmp->prev)
		c = end->col;
	else if (cmp->prev->col > cmp->col)
		c = ind;
	else
		c = cmp->col - 1;
	left_touch2(end, c, &*j, &cmp);
	print_comp_tab(bcmp, 0, i, &*j);
}
