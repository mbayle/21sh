/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lst_comp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 00:47:55 by frameton          #+#    #+#             */
/*   Updated: 2020/02/16 02:16:50 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

static int	init_lst_comp2(t_struct *s, t_lst **l)
{
	while (*s->comp.name)
	{
		if ((*l = malloc(sizeof(**l))) == NULL)
			return (0);
		(*l)->c = *s->comp.name;
		(*l)->prev = s->tmp;
		(*l)->sel = 0;
		(*l)->plc = 0;
		(*l)->line = 0;
		s->tmp->next = *l;
		(*l)->next = NULL;
		s->tmp = *l;
		*l = NULL;
		s->comp.name++;
	}
	s->cpt3 = 1;
	return (1);
}

int			init_lst_comp(char buf[6], t_struct *s, t_lst *l, t_lst *rt)
{
	char	*del;

	del = s->comp.name;
	if (buf[0] == 9)
	{
		if (!(init_lst_comp2(&*s, &l)))
			return (0);
	}
	free(del);
	s->comp.name = NULL;
	rt = s->tmp;
	while (rt)
		rt = rt->prev;
	return (1);
}
