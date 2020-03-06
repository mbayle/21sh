/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recup_stdin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 00:24:27 by frameton          #+#    #+#             */
/*   Updated: 2020/03/03 23:39:35 by frameton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

static int	recup_stdin2(t_struct *s, int *i, t_htr **t, int ret)
{
	s->cpt_p2 = 0;
	s->cpt_p3 = 0;
	s->cpt5 = 0;
	if (!(s->iret = 0) && !(s->lbg))
	{
		if (!(s->tmp))
			*i = 0;
		*t = NULL;
	}
	s->ret = ret;
	return (2);
}

int			recup_stdin(t_struct *s, char buf[701], int *i, int ret)
{
	int				r;
	static t_htr	*t;

	r = recup_stdin2(s, &*i, &t, ret);
	if (buf[0] == ('\n'))
		return (1);
	if (s->comp.name && !(init_lst_comp(buf, &*s, NULL, NULL)))
		return (0);
	if (!s->lbg && s->tmp)
		r = init_lst_4(s, buf, 0, NULL);
	else if (!s->tmp || !s->tmp->next)
		r = init_lst_2(&*s, buf, &*i, &t);
	else if (s->lbg && s->tmp && s->tmp->next)
		r = init_lst_3(&*s, buf, 0, NULL);
	s->iret = s->iret + 1;
	write_lst(s, buf, &s->nl);
	s->set_cpt = 0;
	if (!(s->cpt_p = 0) && r != 3)
		r = 2;
	if (r == -1)
		return (0);
	return (r);
}
