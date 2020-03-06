/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_line1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 00:58:56 by frameton          #+#    #+#             */
/*   Updated: 2020/02/16 05:36:31 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

static int	move_cur(int i, t_lst **tmp, t_lst **lbg)
{
	if (i == 68 && *tmp && (*tmp)->prev)
		*tmp = (*tmp)->prev;
	else if (i == 68 && *tmp && !(*tmp)->prev)
		*lbg = NULL;
	if (i == 67 && *tmp && (*tmp)->next)
		*tmp = (*tmp)->next;
	return (1);
}

static void	push_back_cur(t_struct *s, int i)
{
	(void)i;
	while (s->tmp)
	{
		if (s->tmp->prev)
		{
			s->tmp = s->tmp->prev;
			free(s->tmp->next);
		}
		else
		{
			free(s->tmp);
			s->tmp = NULL;
			s->lbg = NULL;
		}
	}
}

static int	copy_history(t_struct *s, t_lst **lbg, int c, t_htr **t)
{
	if (!*t)
		*t = s->h;
	else if (*t && (*t)->next && c == 65)
		*t = (*t)->next;
	else if (*t && (*t)->prev && c == 66)
		*t = (*t)->prev;
	if ((*lbg = malloc(sizeof(**lbg))) == NULL)
		return (0);
	c = 0;
	(*lbg)->c = (*t)->name[c++];
	(*lbg)->sel = 0;
	(*lbg)->prev = NULL;
	(*lbg)->next = NULL;
	s->tmp = *lbg;
	while ((*t)->name[c])
	{
		if ((s->tmp->next = malloc(sizeof(*s->tmp))) == NULL)
			return (0);
		s->tmp->next->sel = 0;
		s->tmp->next->next = NULL;
		s->tmp->next->prev = s->tmp;
		s->tmp->next->c = (*t)->name[c++];
		s->tmp = s->tmp->next;
	}
	return (1);
}

static void	edi_line_bis(char buf[6], t_struct *s)
{
	if (s->comp.name)
		s->comp.name = NULL;
	if (buf[2] == 72)
	{
		while (s->tmp != s->lbg)
			s->tmp = s->tmp->prev;
		s->lbg = NULL;
	}
}

int			edit_line(t_struct *s, char buf[6], int *i, t_htr **t)
{
	if ((s->c = edit_line_comp(&*s, buf, &*i)) != 4)
		return (s->c);
	if (buf[0] == 27 && buf[1] == 27 && buf[2] == 91
			&& (buf[3] == 67 || buf[3] == 68 || buf[3] == 65 || buf[3] == 66))
		return (move_word(s, buf[3]));
	if ((buf[0] == 27 && buf[1] == 91) && (buf[2] == 68 || buf[2] == 67
			|| buf[2] == 65 || buf[2] == 66 || buf[2] == 70 || buf[2] == 72))
	{
		edi_line_bis(buf, s);
		if ((((buf[2] == 65 && !s->lbg) || (buf[2] == 65 && *t && (*t)->next))
					|| (buf[2] == 66 && s->lbg && *t)) && s->h)
		{
			push_back_cur(&*s, 1);
			if (*t && !(*t)->prev && buf[2] == 66)
			{
				push_back_cur(&*s, 0);
				*t = NULL;
				return (1);
			}
			if (!(*i = copy_history(&*s, &s->lbg, buf[2], &*t)))
				return (-1);
		}
		return (move_cur(buf[2], &s->tmp, &s->lbg));
	}
	return (0);
}
