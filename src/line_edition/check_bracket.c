/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_bracket.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frameton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 18:58:08 by frameton          #+#    #+#             */
/*   Updated: 2020/03/12 13:48:20 by frameton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

int		check_bracket(t_struct *s, char buf[701], int i)
{
	int		c;
	char	stack[256];
	char	*str;

	str = NULL;
	s->l = s->lbg;
	while (s->l && (i = i + 1))
		s->l = s->l->next;
	s->l = s->lbg;
	create_line(&str, s, 0, i);
	c = ft_bracket(str, -1, 0, stack);
	if (c > -1)
		return (sec_free(&str, 0));
	if (c == -1)
		s->b = 1;
	if (c == -2)
		s->p = 1;
	fp("bl", NULL);
	usleep(100000);
	fp("bl", NULL);
	write_lst(s, buf, &s->nl);
	s->p = 0;
	s->b = 0;
	return (sec_free(&str, 1));
}
