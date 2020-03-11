/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bslash_f.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frameton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 17:25:26 by frameton          #+#    #+#             */
/*   Updated: 2020/03/11 17:50:03 by frameton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

int		bsls(t_struct *s, char buf[701])
{
	t_lst	*l;

	l = s->lbg;
	while (l && l->next)
		l = l->next;
	if (!l || l->c != '\\')
		return (1);
	fp("bl", NULL);
	usleep(100000);
	fp("bl", NULL);
	s->bs = 1;
	write_lst(s, buf, &s->nl);
	s->bs = 0;
	return (0);
}
