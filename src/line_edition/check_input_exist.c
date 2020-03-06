/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input_exist.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 01:18:12 by frameton          #+#    #+#             */
/*   Updated: 2020/02/16 02:16:50 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

int		check_input_exist2(t_struct *s, int *i, int *c)
{
	s->l = s->lbg;
	*i = 0;
	*c = 0;
	while (s->l)
	{
		if (check_whitespaces(s->l->c))
			return (2);
		(*c)++;
		s->l = s->l->next;
	}
	s->l = s->lbg;
	return (1);
}

int		check_input_exist3(t_struct s, int c, int i, t_htr *com)
{
	char	*line;

	c = 0;
	line = NULL;
	s.l = s.lbg;
	while (s.l && (c = c + 1))
		s.l = s.l->next;
	s.l = s.lbg;
	if (!(create_line(&line, &s, 0, c)))
		return (0);
	s.l = s.lbg;
	while (*s.builtin_ref)
	{
		if (!(ft_strcmp(line, *s.builtin_ref)))
			return (sec_free(&line, 1));
		s.builtin_ref++;
	}
	while (com)
	{
		if (!(ft_strcmp(line, com->name)))
			i = 1;
		com = com->next;
	}
	return (sec_free(&line, i));
}

int		check_input_exist(t_struct s, t_htr *com)
{
	int		c;
	int		i;
	int		d;
	t_htr	*cm;

	cm = com;
	d = check_input_exist2(&s, &i, &c);
	if (d == 2 && s.cki)
		return (1);
	i = check_input_exist3(s, c, i, cm);
	if (i)
		return (1);
	return (0);
}
