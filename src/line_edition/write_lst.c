/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 00:16:13 by frameton          #+#    #+#             */
/*   Updated: 2020/02/16 02:16:50 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

static void		set_plc(t_struct *s, int *i, int l)
{
	int		c;

	s->row = 0;
	c = s->coprompt;
	*i = s->col;
	s->l = s->lbg;
	while (s->l)
	{
		s->l->plc = c++;
		s->l->line = l;
		if (s->l->plc == *i)
		{
			++l;
			s->l->line = l;
			*i = *i + s->col;
		}
		if (!(s->l->next) && (*i = s->col))
			break ;
		s->l = s->l->next;
	}
	--c;
	while (c >= *i && (*i = *i + s->col))
		s->row++;
	fp("cr", NULL);
}

static int		move_up_down(char buf[6], t_struct *s, int *lbg)
{
	int		i;
	int		ref;

	i = s->col;
	if (buf[0] == 27 && buf[1] == 27 && buf[2] == 91
			&& (buf[3] == 65))
	{
		ref = s->tmp->plc - s->col;
		while (s->tmp->prev && s->tmp->prev->plc >= ref)
			s->tmp = s->tmp->prev;
	}
	else if (buf[0] == 27 && buf[1] == 27 && buf[2] == 91
			&& (buf[3] == 66))
	{
		ref = s->tmp->plc + s->col;
		while (s->tmp->next && s->tmp->next->plc <= ref)
			s->tmp = s->tmp->next;
	}
	else
		return (0);
	if (s->tmp == s->lbg)
		*lbg = 1;
	if (*lbg && s->tmp != s->lbg)
		*lbg = 0;
	return (0);
}

static void		check_sel(t_struct *s)
{
	t_lst	*sel;
	t_lst	*bg;

	bg = s->lbg;
	while (bg)
	{
		if (bg->sel)
		{
			sel = bg->next;
			while (sel && !sel->sel)
				sel = sel->next;
			if (!sel)
				break ;
			else
				while (bg != sel)
				{
					bg->sel = 1;
					bg = bg->next;
				}
		}
		else
			bg = bg->next;
	}
}

void			write_lst(t_struct *s, char buf[6], int *nl)
{
	int			i;
	static int	pc;
	int			lbg;

	fp("vi", NULL);
	if (!s->lbg && s->tmp && (lbg = 1))
		s->lbg = s->tmp;
	else
		lbg = 0;
	check_sel(s);
	move_up_down(buf, s, &lbg);
	set_plc(s, &i, 0);
	while (pc < *nl && (pc = pc + 1))
		tputs(tgetstr("do", NULL), 1, ft_ptchar);
	while ((*nl)--)
		fp("dl", "up");
	s->cki = print_lst(*s, &*nl, 0);
	free_bcom(s);
	set_pos_cur(s, i, *nl, &pc);
	if (lbg && !(s->lbg = NULL))
		tputs(tgetstr("le", NULL), 1, ft_ptchar);
	s->cpt3 = 0;
	s->eq = 0;
	s->edq = 0;
	fp("ve", NULL);
}
