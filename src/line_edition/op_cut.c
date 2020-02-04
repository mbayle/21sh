/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_cut.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frameton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 00:27:30 by frameton          #+#    #+#             */
/*   Updated: 2020/02/03 22:14:01 by frameton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	op_cut2(t_struct *s, t_lst **end, t_lst **bg, int lbg)
{
	*end = *bg;
	while (*end && (*end)->sel)
		*end = (*end)->next;
	if (!*end)
	{
		s->tmp = NULL;
		if (lbg)
			s->lbg = NULL;
		return (free_sel(&*bg, &*end));
	}
	(*end)->prev = NULL;
	if (lbg)
	{
		s->lbg = *end;
		s->tmp = s->lbg;
	}
	else
		s->tmp = *end;
	s->lbg = NULL;
	return (free_sel(&*bg, &*end));
}

static void	op_cut4(t_lst **del, t_lst **bg, t_lst **end)
{
	*del = *bg;
	*bg = (*bg)->next;
	free_sel(&*bg, &*end);
	(*end)->prev = *del;
	(*del)->next = *end;
}

static int	op_cut3(t_lst **bg, t_lst **end, t_struct *s, int lbg)
{
	t_lst	*del;

	while (*bg && (*bg)->next && !(*bg)->next->sel)
		*bg = (*bg)->next;
	if (!(*bg)->next)
		return (1);
	*end = (*bg)->next;
	while (*end && (*end)->sel)
		*end = (*end)->next;
	if (!*end)
	{
		del = *bg;
		if (lbg && (s->tmp = s->lbg))
			s->lbg = NULL;
		*bg = (*bg)->next;
		free_sel(&*bg, &*end);
		del->next = NULL;
		return (1);
	}
	op_cut4(&del, bg, end);
	if (lbg && (s->tmp = s->lbg))
		s->lbg = NULL;
	return (0);
}

int			op_cut(t_struct *s, int i)
{
	t_lst	*bg;
	t_lst	*end;
	int		lbg;

	if (i == 1 && !(lbg = 0))
		bg = s->tmp;
	if (i > 1 && (lbg = 1))
		bg = s->lbg;
	if (bg->sel)
		return (op_cut2(s, &end, &bg, lbg));
	return (op_cut3(&bg, &end, s, lbg));
}
