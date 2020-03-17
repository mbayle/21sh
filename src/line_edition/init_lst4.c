/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lst4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 00:46:08 by frameton          #+#    #+#             */
/*   Updated: 2020/03/05 22:39:02 by frameton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

static int	init_lst_4_b(char buf[701], t_struct *s)
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

static	int	init_lst_4_b2(t_struct *s, char buf[701])
{
	if (!s->tmp->sel)
		s->tmp->sel = 1;
	else
		s->tmp->sel = 0;
	if (buf[5] == 67)
		s->lbg = s->tmp;
	return (1);
}

int			init_lst_4(t_struct *s, char buf[701], int c, t_lst *l)
{
	if ((edit_line3(s, buf)) || (buf[0] == 18))
		return (1);
	if (buf[0] == 27 && buf[1] == 91 && buf[2] == 49
			&& buf[3] == 59 && buf[4] == 50)
		return (init_lst_4_b2(s, buf));
	if ((buf[0] == -49 && buf[1] == -128)
			|| (buf[0] == -62 && buf[1] == -82)
			|| (buf[0] == -30 && buf[1] == -120 && buf[2] == -126))
		return (cpc(s, buf[1], 1));
	if (buf[0] == 27 && buf[1] == 79 && (buf[2] == 80 || buf[2] == 81))
		return (init_lst_4_b(buf, s));
	if (buf[c] < 0 || buf[c] > 127)
		return (1);
	if ((l = malloc(sizeof(*l))) == NULL)
		return (-1);
	l->c = buf[0];
	l->sel = 0;
	l->next = s->tmp;
/*	*/if ((s->tmp = malloc(sizeof(*l))) == NULL)
		return (-1);
	s->tmp->prev = l;
	l->prev = NULL;
	s->lbg = l;
	s->lbg->next = 0;
	s->tmp = s->lbg;
	if (ft_strlen(buf) > 1)
		return (init_lst_3(s, buf, 1, NULL));
	return (2);
}
