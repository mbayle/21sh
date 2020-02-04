/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lst3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frameton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 00:55:10 by frameton          #+#    #+#             */
/*   Updated: 2020/01/25 00:55:11 by frameton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	init_lst_3_b(t_struct *s, char buf[5])
{
	if (!s->tmp->next->sel)
		s->tmp->next->sel = 1;
	else
		s->tmp->next->sel = 0;
	if (buf[5] == 68)
	{
		if (s->tmp->prev)
			s->tmp = s->tmp->prev;
		else if (!s->tmp->prev)
			s->lbg = NULL;
	}
	if (buf[5] == 67)
		if (s->tmp->next)
			s->tmp = s->tmp->next;
	return (1);
}

static int	init_lst_3_b2(t_struct *s, char buf[5])
{
	if (buf[2] == 81)
	{
		if (s->cpt < 5)
			s->cpt++;
		else
			tputs(tgetstr("bl", NULL), 1, ft_ptchar);
	}
	else
	{
		if (s->cpt > 1)
			s->cpt--;
		else
			tputs(tgetstr("bl", NULL), 1, ft_ptchar);
	}
	s->set_cpt = 1;
	return (1);
}

int			init_lst_3(t_struct *s, char buf[5], int c, t_lst *l)
{
	if ((edit_line2(&s->lbg, &s->tmp, buf)))
		return (ft_completion(&*s, NULL, buf, 0));
	if (buf[0] == 27 && buf[1] == 91 && buf[2] == 49 && buf[3] == 59
			&& buf[4] == 50)
		return (init_lst_3_b(s, buf));
	if (buf[0] == 18)
		return (1);
	if ((buf[0] == -49 && buf[1] == -128)
			|| (buf[0] == -62 && buf[1] == -82)
			|| (buf[0] == -30 && buf[1] == -120 && buf[2] == -126))
		return (cpc(s, buf[1], 2));
	if (buf[0] == 27 && buf[1] == 79 && (buf[2] == 80 || buf[2] == 81))
		return (init_lst_3_b2(s, buf));
	if ((l = malloc(sizeof(*l))) == NULL)
		return (-1);
	l->c = buf[c];
	l->sel = 0;
	l->next = s->tmp->next;
	l->prev = s->tmp;
	s->tmp->next->prev = l;
	s->tmp->next = l;
	s->tmp = s->tmp->next;
	l = l->next;
	return (2);
}
