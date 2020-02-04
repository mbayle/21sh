/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recup_stdin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frameton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 00:24:27 by frameton          #+#    #+#             */
/*   Updated: 2020/01/25 01:28:13 by frameton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	recup_stdin2(t_struct *s, int *i, t_htr **t)
{
	if (!(s->iret = 0) && !(s->lbg))
	{
		if (!(s->tmp))
			*i = 0;
		*t = NULL;
	}
}

int			recup_stdin(t_struct *s, char buf[5], int *i, int ret)
{
	int				r;
	static t_htr	*t;

	recup_stdin2(s, &*i, &t);
	r = 2;
	if (s->comp.name && !(init_lst_comp(buf, &*s, NULL, NULL)))
		return (0);
	while (r == 2 && s->iret < ret)
	{
		if (!s->lbg && s->tmp)
			r = init_lst_4(s, buf, s->iret, NULL);
		else if (!s->tmp || !s->tmp->next)
			r = init_lst_2(&*s, buf, &*i, &t);
		else if (s->lbg && s->tmp && s->tmp->next)
			r = init_lst_3(&*s, buf, s->iret, NULL);
		s->iret = s->iret + 1;
		write_lst(s, buf, &s->nl);
		s->set_cpt = 0;
	}
	if (r != 3)
		r = 2;
	if (r == -1)
		return (0);
	return (r);
}
