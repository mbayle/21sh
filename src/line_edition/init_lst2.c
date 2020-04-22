/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lst2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 00:48:13 by frameton          #+#    #+#             */
/*   Updated: 2020/03/07 20:52:24 by frameton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

static void	init_lst_2b(t_struct *s, int *i, t_lst **l, t_htr **t)
{
	if (!*i && !*t)
	{
		(*l)->prev = NULL;
		s->lbg = *l;
		s->tmp = *l;
		*i = 1;
	}
	else
	{
		(*l)->prev = s->tmp;
		s->tmp->next = *l;
		s->tmp = s->tmp->next;
	}
	if (s->comp.name)
	{
		ft_putchar((*l)->c);
		s->comp.name = NULL;
	}
}

static int	init_lst_2_b(t_struct *s, char buf[6])
{
	if (!s->lbg && !s->tmp)
		return (1);
	if (!s->tmp->sel)
		s->tmp->sel = 1;
	else
		s->tmp->sel = 0;
	if (buf[5] == 68)
		if (s->tmp->prev)
			s->tmp = s->tmp->prev;
	if (buf[5] == 67)
		if (s->tmp->next)
			s->tmp = s->tmp->next;
	return (1);
}

static int	init_lst_2_b2(t_struct *s, char buf[6])
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

static int	init_lst_2_b3(t_struct *s, char buf[6])
{
	if ((buf[0] == 127 || (buf[0] == 27 && buf[3] == 126)) && (s->cpt > 3))
		return (ft_completion(&*s, NULL, buf, 2));
	if (buf[0] == 9 && s->cpt == 1)
		return (1);
	return (ft_completion(&*s, NULL, buf, 0));
}

int			init_lst_2(t_struct *s, char buf[701], int *i, t_htr **t)
{
	t_lst	*l;
	int		c;
	int		a;

	c = 0;
	if (edit_line(&*s, buf, &*i, &*t))
		return (init_lst_2_b3(s, buf));
	if ((buf[0] == -49 && buf[1] == -128) || (buf[0] == -62 && buf[1] == -82)
			|| (buf[0] == -30 && buf[1] == -120 && buf[2] == -126))
		return (cpc(s, buf[1], 3));
	if (buf[0] == 18 && !s->lbg)
		return (ctrl_r(s));
	if (buf[0] == 27 && buf[1] == 91 && buf[2] == 49 && buf[3] == 59
			&& buf[4] == 50)
		return (init_lst_2_b(s, buf));
	if (buf[0] == 27 && buf[1] == 79 && (buf[2] >= 80 || buf[2] <= 83))
		return (init_lst_2_b2(s, buf));
	while (buf[c])
	{
		if ((a = init_lst2_b4(buf, &l, &c)) == -1 || a == 1)
			return (a);
		init_lst_2b(&*s, &*i, &l, &*t);
		++c;
	}
	return (ft_completion(&*s, NULL, buf, 0));
}
