/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 01:17:41 by frameton          #+#    #+#             */
/*   Updated: 2020/03/03 22:09:01 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

void	reset_sel(t_struct *s)
{
	t_lst	*r;

	if (!s->lbg)
		r = s->tmp;
	else
		r = s->lbg;
	while (r)
	{
		r->sel = 0;
		r = r->next;
	}
}

int		free_sel(t_lst **bg, t_lst **end)
{
	t_lst	*del;

	while (*bg && *bg != *end)
	{
		del = (*bg)->next;
		free(*bg);
		*bg = del;
	}
	return (1);
}

int		create_char(t_lst **end, char c)
{
	t_lst	*new;

	if ((new = malloc(sizeof(*new))) == NULL)
		return (0);
	new->next = NULL;
	new->c = c;
	new->sel = 0;
	new->prev = *end;
	new->plc = 0;
	new->line = 0;
	(*end)->next = new;
	*end = (*end)->next;
	return (1);
}

int		cpc(t_struct *s, char b, int i)
{
	if (i == 3 && !s->lbg && b != -128)
		return (1);
	if (b == -120)
		if (!op_copy(s, i, &s->cpcl))
			return (0);
	if (b == -82)
		op_cut(s, i);
	if (b == -128)
		op_paste(s, &s->cpcl);
	return (1);
}
