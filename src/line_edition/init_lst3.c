/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lst3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 00:55:10 by frameton          #+#    #+#             */
/*   Updated: 2020/03/05 22:42:24 by frameton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

static int	init_lst_3_b(t_struct *s, char buf[6])
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

static int	init_lst_3_b2(t_struct *s, char buf[6])
{
	if (buf[2] == 81)
	{
		if (s->cpt < 5)
			s->cpt++;
		else
			tputs(tgetstr("bl", NULL), 1, ft_ptchar);
	}
	if (buf[2] == 80)
	{
		if (s->cpt > 1)
			s->cpt--;
		else
			tputs(tgetstr("bl", NULL), 1, ft_ptchar);
	}
	if ((buf[2] == 82 && !s->clr) || (buf[2] == 83 && s->clr == 13))
		fp("bl", NULL);
	else if (buf[2] == 82 && s->clr)
		s->clr--;
	else if (buf[2] == 83 && s->clr < 13)
		s->clr++;
	if (buf[2] < 82)
		s->set_cpt = 1;
	return (1);
}

static void	init_lst_3_b3(t_struct *s, t_lst **l)
{
	(*l)->sel = 0;
	(*l)->next = s->tmp->next;
	(*l)->prev = s->tmp;
	s->tmp->next->prev = *l;
	s->tmp->next = *l;
	s->tmp = s->tmp->next;
	*l = (*l)->next;
}

int			init_lst_3(t_struct *s, char buf[701], int c, t_lst *l)
{
	if ((edit_line2(s, &s->lbg, &s->tmp, buf)))
		return (ft_completion(&*s, NULL, buf, 0));
	if (buf[0] == 27 && buf[1] == 91 && buf[2] == 49 && buf[3] == 59
			&& buf[4] == 50)
		return (init_lst_3_b(s, buf));
	if (buf[0] == 18)
		return (1);
	if ((buf[0] == -49 && buf[1] == -128) || (buf[0] == -62 && buf[1] == -82)
			|| (buf[0] == -30 && buf[1] == -120 && buf[2] == -126))
		return (cpc(s, buf[1], 2));
	if (buf[0] == 27 && buf[1] == 79 && (buf[2] == 80 || buf[2] == 81))
		return (init_lst_3_b2(s, buf));
	while (buf[c])
	{
		if (ft_myisascii(buf[0]) == 0)
			return (1);
		if ((l = malloc(sizeof(*l))) == NULL)
			return (-1);
		l->c = buf[c];
		init_lst_3_b3(s, &l);
		++c;
	}
	return (2);
}
