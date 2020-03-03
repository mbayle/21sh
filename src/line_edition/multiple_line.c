/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 00:33:27 by frameton          #+#    #+#             */
/*   Updated: 2020/03/03 22:09:01 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

static void		set_pos_cur2(t_struct *s, int i, int *pc)
{
	while (s->l->line == i && (s->l = s->l->prev))
		tputs(tgetstr("le", NULL), 1, ft_ptchar);
	--i;
	while (s->l->prev && s->l->prev->line == i)
		s->l = s->l->prev;
	tputs(tgetstr("up", NULL), 1, ft_ptchar);
	--(*pc);
	while (s->l->plc > s->tmp->plc)
	{
		--i;
		while (s->l->prev && s->l->prev->line == i)
			s->l = s->l->prev;
		tputs(tgetstr("up", NULL), 1, ft_ptchar);
		--(*pc);
	}
	if (!s->tmp->line && (i = s->coprompt))
		while (i--)
			tputs(tgetstr("nd", NULL), 1, ft_ptchar);
	while (s->l != s->tmp && (s->l = s->l->next))
		tputs(tgetstr("nd", NULL), 1, ft_ptchar);
}

void			set_pos_cur(t_struct *s, int i, int nl, int *pc)
{
	i = nl;
	*pc = nl;
	if (!s->tmp || s->tmp->line == i)
	{
		while (s->tmp && s->l != s->tmp)
		{
			s->l = s->l->prev;
			tputs(tgetstr("le", NULL), 1, ft_ptchar);
		}
	}
	else
		set_pos_cur2(s, i, pc);
}
