/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_line2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 00:59:40 by frameton          #+#    #+#             */
/*   Updated: 2020/03/03 22:09:01 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

static int	delete_char(t_lst **lbg, t_lst **tmp)
{
	if (!(*tmp)->prev)
	{
		*tmp = (*tmp)->next;
		free((*tmp)->prev);
		(*tmp)->prev = NULL;
		*lbg = NULL;
		return (1);
	}
	if ((*tmp)->prev)
	{
		(*tmp)->prev->next = (*tmp)->next;
		*tmp = (*tmp)->prev;
		free((*tmp)->next->prev);
		(*tmp)->next->prev = *tmp;
	}
	return (1);
}

static int	move_cur2(t_lst **tmp, t_lst **lbg, char buf[6])
{
	if (buf[2] == 68 && *tmp)
	{
		if ((*tmp)->prev)
			*tmp = (*tmp)->prev;
		else
			*lbg = NULL;
	}
	if (buf[2] == 67 && (*tmp)->next)
		*tmp = (*tmp)->next;
	return (1);
}

static void	move_cur(t_lst **tmp, t_lst **lbg, char buf[6])
{
	if ((buf[2] == 65 || buf[2] == 70) && *tmp)
		while (*tmp && (*tmp)->next)
			*tmp = (*tmp)->next;
	if ((buf[2] == 66 || buf[2] == 72) && *tmp)
	{
		while (*tmp != *lbg)
			*tmp = (*tmp)->prev;
		*lbg = NULL;
	}
}

static int	check_sign(t_struct *s, char buf[6], t_lst *del, int c)
{
	if (buf[0] == 3 && s->iret == 1)
	{
		c = s->tmp->line;
		while (c < s->nl && (c = c + 1))
			fp("do", NULL);
		s->nl = 0;
		ft_putchar('\n');
		free_lst(s);
	}
	if (buf[0] == 4 && s->iret == 1)
		if (s->tmp && s->tmp->next)
		{
			if (s->tmp->next->next && (del = s->tmp->next))
			{
				s->tmp->next->next->prev = s->tmp;
				s->tmp->next = s->tmp->next->next;
				free(del);
			}
			else
			{
				free(s->tmp->next);
				s->tmp->next = NULL;
			}
		}
	return (1);
}

int			edit_line2(t_struct *s, t_lst **lbg, t_lst **tmp, char buf[6])
{
	if (buf[0] == 27 && buf[1] == 27 && buf[2] == 91
	&& (buf[3] == 67 || buf[3] == 68 || buf[3] == 65 || buf[3] == 66))
		return (edl2_move_word(lbg, tmp, buf[3]));
	if ((buf[0] == 127 || (buf[0] == 27 && buf[3] == 126)))
		return (delete_char(&*lbg, &*tmp));
	if ((buf[0] == 27 && buf[1] == 91) && (buf[2] == 68 || buf[2] == 67
			|| buf[2] == 65 || buf[2] == 66 || buf[2] == 72 || buf[2] == 70))
	{
		if (*tmp && (buf[2] == 65 || buf[2] == 66
					|| buf[2] == 70 || buf[2] == 72))
			move_cur(&*tmp, &*lbg, buf);
		return (move_cur2(&*tmp, &*lbg, buf));
	}
	if (buf[0] == 9)
	{
		fp("bl", NULL);
		return (1);
	}
	if ((buf[0] == 3 || buf[0] == 4) && s->iret == 1)
		return (check_sign(s, buf, NULL, 0));
	return (0);
}
