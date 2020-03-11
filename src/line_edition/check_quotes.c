/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 00:07:50 by frameton          #+#    #+#             */
/*   Updated: 2020/03/11 19:46:31 by frameton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

static char	*check_quotes3(int *d, int *s, char *c, char *save)
{
	if (*save == '\'' && (*c == *save || !*c))
	{
		if (*s)
			(*s)--;
		else
			(*s)++;
		if (!*s)
			*c = '\'';
		else
			*c = 0;
	}
	if (*save == '"' && (*c == *save || !*c))
	{
		if (*d)
			(*d)--;
		else
			(*d)++;
		if (!*d)
			*c = '"';
		else
			*c = 0;
	}
	save++;
	return (save);
}

static void	indicator_quotes(t_struct *st, char buf[6], int s, int d)
{
	int			i;
	int			c;
	static int	red;

	i = st->eq;
	c = st->edq;
	usleep(100000);
	if (!red)
		red = 1;
	else
		red = 0;
	if (!red && !s)
		st->eq = 1;
	if (!red && !d)
		st->edq = 1;
	write_lst(st, buf, &st->nl);
	st->eq = i;
	st->edq = c;
}

static void	check_quotes2_b(t_struct *st, char buf[6], int s, int d)
{
	write_lst(st, buf, &st->nl);
	indicator_quotes(st, buf, s, d);
	indicator_quotes(st, buf, s, d);
	indicator_quotes(st, buf, s, d);
	indicator_quotes(st, buf, s, d);
}

static int	check_quotes2(t_struct *st, char **str, char buf[6], int s)
{
	char	*save;
	int		d;
	char	c;

	d = 1;
	c = 0;
	save = *str;
	while (*save)
		if (*save == '\\')
			check_bslash(&save);
		else
			save = check_quotes3(&d, &s, &c, save);
	if (!s || !d)
	{
		if (!s)
			st->eq = 1;
		if (!d)
			st->edq = 1;
		check_quotes2_b(st, buf, s, d);
		return (sec_free(str, 0));
	}
	return (sec_free(str, 1));
}

int			check_quotes(t_struct *s, char buf[6])
{
	int		c;
	char	*l;

	c = 0;
	l = NULL;
	if (!s->lbg && !s->tmp)
		return (1);
	s->l = s->lbg;
	while (s->l && (c = c + 1))
		s->l = s->l->next;
	s->l = s->lbg;
	if (!(create_line(&l, s, 0, c)))
		return (-1);
	return (check_quotes2(s, &l, buf, 1));
}
