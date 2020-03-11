/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_bracket.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frameton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 18:58:08 by frameton          #+#    #+#             */
/*   Updated: 2020/03/11 19:14:49 by frameton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

int		check_bracket(t_struct *s, char buf[701])
{
	int		c;

	c = ft_bracket()
	if (c > -1)
		return (1);
	if (c == -1)
		s->b = 1;
	if (c == -2)
		s->p = 1;
	fp("bl", NULL);
	usleep(100000);
	fp("bl", NULL);
	write_lst(st, buf, &st->nl);
	s->p = 0;
	s->b = 0;
}
