/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_r2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 01:14:20 by frameton          #+#    #+#             */
/*   Updated: 2020/03/10 23:59:42 by frameton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

int		check_char_ctrl_r(char buf[5], int ret)
{
	if (ret > 3 && buf[0] == 27 && buf[3] == 126)
		return (0);
	if ((buf[0] == 27 || buf[0] == 3 || buf[0] == 4) && ret == 1)
		return (1);
	if (ret > 1)
		return (1);
	if (buf[0] < 32 || buf[0] > 127)
		return (1);
	return (0);
}

t_htr	*check_htr(t_htr *t, char *l)
{
	int		c;
	char	*s;

	c = 0;
	while (t)
	{
		s = t->name;
		while (*s)
		{
			if (!(ft_strncmp(s, l, ft_strlen(l))))
				return (t);
			s++;
		}
		t = t->next;
	}
	return (t);
}

char	*new_l(char **l)
{
	char	*new;
	char	*bg;
	char	*del;
	int		c;

	c = ft_strlen(*l) - 1;
	if (!c)
	{
		sec_free(l, 0);
		return (NULL);
	}
	del = *l;
	if ((new = (char*)malloc(sizeof(*new) * (ft_strlen(del)))) == NULL)
		return (NULL);
	bg = new;
	while (c--)
	{
		*new = *del;
		new++;
		del++;
	}
	*new = '\0';
	sec_free(l, 0);
	return (bg);
}

int		ctrl_r2_b(char **l, char buf[6])
{
	char	*del;

	del = *l;
	if ((*l = ft_strjoin(*l, buf)) == NULL)
	{
		fp("ve", NULL);
		return (sec_free(&del, 0));
	}
	return (sec_free(&del, 1));
}

int		change_lst(t_struct *s, t_htr *t, int c)
{
	s->lbg = NULL;
	s->tmp = NULL;
	if ((s->lbg = malloc(sizeof(*s->lbg))) == NULL)
		return (0);
	s->lbg->c = t->name[c++];
	s->lbg->sel = 0;
	s->lbg->plc = 0;
	s->lbg->line = 0;
	s->lbg->prev = NULL;
	s->lbg->next = NULL;
	s->tmp = s->lbg;
	ft_putendl(t->name);
	while (t->name[c])
	{
		if ((s->tmp->next = malloc(sizeof(*s->tmp))) == NULL)
			return (0);
		s->tmp->next->sel = 0;
		s->tmp->next->plc = 0;
		s->tmp->next->line = 0;
		s->tmp->next->next = NULL;
		s->tmp->next->prev = s->tmp;
		s->tmp->next->c = t->name[c++];
		s->tmp = s->tmp->next;
	}
	return (1);
}
