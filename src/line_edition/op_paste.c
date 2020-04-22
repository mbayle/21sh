/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_paste.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 00:31:42 by frameton          #+#    #+#             */
/*   Updated: 2020/02/16 02:16:50 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

static t_lst	*op_paste2(t_lst **end, t_lst *bg, char **l, int *c)
{
	if ((bg = malloc(sizeof(*bg))) == NULL)
		return (NULL);
	bg->c = (*l)[*c];
	bg->sel = 0;
	bg->prev = NULL;
	bg->next = NULL;
	bg->plc = 0;
	bg->line = 0;
	*end = bg;
	(*c)++;
	while ((*l)[*c])
	{
		create_char(&*end, (*l)[*c]);
		(*c)++;
	}
	return (bg);
}

static int		op_paste3(t_struct *s, t_lst *end, t_lst *bg)
{
	if (!s->tmp)
	{
		s->lbg = bg;
		s->tmp = end;
		return (1);
	}
	s->tmp->prev = end;
	end->next = s->tmp;
	s->tmp = end;
	s->lbg = bg;
	return (1);
}

int				op_paste(t_struct *s, char **l)
{
	t_lst	*bg;
	t_lst	*end;
	int		c;

	c = 0;
	end = NULL;
	if (!*l)
		return (1);
	if (!(bg = op_paste2(&end, NULL, &*l, &c)))
		return (0);
	if (!s->lbg)
		return (op_paste3(s, end, bg));
	if (!s->tmp->next)
	{
		s->tmp->next = bg;
		bg->prev = s->tmp;
		s->tmp = end;
		return (1);
	}
	s->tmp->next->prev = end;
	end->next = s->tmp->next;
	s->tmp->next = bg;
	bg->prev = s->tmp;
	s->tmp = end;
	return (1);
}
