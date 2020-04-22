/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_line3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 01:00:04 by frameton          #+#    #+#             */
/*   Updated: 2020/02/16 05:37:46 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

int			del_move(int c)
{
	while (c--)
	{
		tputs(tgetstr("le", NULL), 1, ft_ptchar);
		tputs(tgetstr("dc", NULL), 1, ft_ptchar);
	}
	return (1);
}

static int	move_cur(t_struct *s, char buf[6])
{
	if ((buf[2] == 65 || buf[2] == 70) && s->tmp)
	{
		s->lbg = s->tmp;
		while (s->tmp && s->tmp->next)
			s->tmp = s->tmp->next;
	}
	if (buf[2] == 67)
		s->lbg = s->tmp;
	return (1);
}

static	int	move_word_edl3(t_struct *s, int c)
{
	t_lst	*tp;

	if (c == 68 || c == 66 || c == 65)
		return (1);
	s->lbg = s->tmp;
	while (s->tmp->next && !(check_whitespaces((s->tmp->next->c))))
		s->tmp = s->tmp->next;
	tp = s->tmp->next;
	while (tp && check_whitespaces(tp->c))
		tp = tp->next;
	if (tp && tp != s->tmp && !(check_whitespaces(tp->c)))
		s->tmp = tp->prev;
	return (1);
}

static int	check_sign(t_struct *s, char buf[6], t_lst *del, int c)
{
	if (buf[0] == 3 && s->ret == 1)
	{
		while (c < s->nl && (c = c + 1))
			fp("do", NULL);
		s->nl = 0;
		ft_putchar('\n');
		free_lst(s);
	}
	if (buf[0] == 4 && s->ret == 1)
	{
		if (s->tmp && s->tmp->next)
		{
			del = s->tmp;
			s->tmp = s->tmp->next;
			s->tmp->prev = NULL;
			free(del);
		}
		else if (!s->tmp->next)
		{
			free(s->tmp);
			s->tmp = NULL;
		}
	}
	return (1);
}

int			edit_line3(t_struct *s, char buf[701])
{
	if (buf[0] == 27 && buf[1] == 27 && buf[2] == 91
	&& (buf[3] == 67 || buf[3] == 68 || buf[3] == 65 || buf[3] == 66))
		return (move_word_edl3(s, buf[3]));
	if ((buf[0] == 127 || (buf[0] == 27 && buf[3] == 126)))
		return (1);
	if ((buf[0] == 27 && buf[1] == 91) && (buf[2] == 68 || buf[2] == 67
			|| buf[2] == 65 || buf[2] == 66 || buf[2] == 70 || buf[2] == 72))
		return (move_cur(s, buf));
	if (buf[0] == 9)
	{
		fp("bl", NULL);
		return (1);
	}
	if ((buf[0] == 3 || buf[0] == 4) && s->ret == 1)
		return (check_sign(s, buf, NULL, 0));
	return (0);
}
