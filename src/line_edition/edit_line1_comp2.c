/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_line1_comp2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 23:44:42 by frameton          #+#    #+#             */
/*   Updated: 2020/03/03 22:09:01 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

int			check_sign_edl1(t_struct *s, char buf[6])
{
	if (buf[0] == 3 && s->iret == 1)
	{
		s->nl = 0;
		ft_putchar('\n');
		free_lst(s);
	}
	if (buf[0] == 4 && s->iret == 1)
		if (!s->tmp)
			s->ctrl_d = 1;
	return (1);
}

int			check_slash(t_struct *s, char **l)
{
	t_lst		*lst;
	int			c;

	c = 0;
	lst = s->l;
	while (lst->next)
		lst = lst->next;
	if (lst->c == '/')
		return (0);
	if ((lst->next = malloc(sizeof(*lst))) == NULL)
		return (1);
	lst->next->next = NULL;
	lst->next->prev = lst;
	lst->next->sel = 0;
	lst->next->c = '/';
	lst = lst->next;
	s->tmp = lst;
	lst = s->l;
	while (lst && (c = c + 1))
		lst = lst->next;
	sec_free(l, 0);
	create_line(l, s, 0, c);
	return (1);
}

static int	check_part_compb(t_struct *s)
{
	while (s->l && s->l->next)
	{
		if (s->l->c == ';')
		{
			s->l = s->l->next;
			return (check_part_comp(s, 1));
		}
		s->l = s->l->next;
	}
	if (check_whitespaces(s->l->c))
	{
		s->l = s->l->next;
		return (2);
	}
	else
	{
		while (!(check_whitespaces(s->l->prev->c)))
			s->l = s->l->prev;
		return (3);
	}
}

int			check_part_comp(t_struct *s, int i)
{
	if (!i && (!s->l || check_whitespaces(s->l->c)))
		return (0);
	if (i)
		while (s->l->next && check_whitespaces(s->l->c))
			s->l = s->l->next;
	while (s->l->next && !(check_whitespaces(s->l->next->c)))
	{
		if (s->l->c == ';')
		{
			s->l = s->l->next;
			return (check_part_comp(s, 1));
		}
		s->l = s->l->next;
	}
	if (!(s->l->next))
	{
		if (!i)
			s->l = s->lbg;
		else
			while (!(check_whitespaces(s->l->prev->c)))
				s->l = s->l->prev;
		return (1);
	}
	return (check_part_compb(s));
}
