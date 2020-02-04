/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_char.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frameton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 01:14:44 by frameton          #+#    #+#             */
/*   Updated: 2020/02/03 23:12:28 by frameton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		del_char(char buf[5], t_struct *s, int *i)
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
