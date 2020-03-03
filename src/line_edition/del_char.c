/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_char.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 00:10:00 by frameton          #+#    #+#             */
/*   Updated: 2020/03/03 22:09:01 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

int		del_char1(char buf[6], t_struct *s, int *i)
{
	if ((buf[0] == 127 || (buf[0] == 27 && buf[3] == 126)))
	{
		if (!s->tmp && !s->comp.name)
			return (1);
		if ((s->tmp)->prev)
		{
			s->tmp = s->tmp->prev;
			free(s->tmp->next);
			s->tmp->next = NULL;
		}
		else
		{
			*i = 0;
			free(s->tmp);
			s->tmp = NULL;
			s->lbg = NULL;
		}
		if (s->comp.name)
		{
			free(s->comp.name);
			s->comp.name = NULL;
		}
		return (1);
	}
	return (0);
}
