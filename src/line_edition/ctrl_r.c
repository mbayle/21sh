/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_r.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 01:12:41 by frameton          #+#    #+#             */
/*   Updated: 2020/03/10 20:01:27 by frameton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

static int	ctrl_r2(char buf[6], t_htr **t, t_struct *s, char **l)
{
	fp("cl", NULL);
	ft_putstr("bck-i-search: ");
	if ((*t = s->h) && (buf[0] == 127 || (buf[0] == 27 && buf[3] == 126)))
	{
		if (*l)
			*l = new_l(l);
		else
			sec_free(l, 0);
	}
	else if (!*l)
	{
		sec_free(l, 0);
		if ((*l = ft_mstrcpy(*l, buf)) == NULL)
		{
			fp("ve", NULL);
			return (0);
		}
	}
	else
	{
		if (!(ctrl_r2_b(l, buf)))
			return (0);
	}
	ft_2putstr(*l, "_\n");
	return (1);
}

static void	ctrl_r3(char **l, t_htr **t, t_htr **st)
{
	if (*l)
		*t = check_htr(*t, *l);
	if (*t && *l)
	{
		ft_putstr(GREEN"> "WHITE);
		ft_putstr((*t)->name);
		*st = *t;
	}
	else
	{
		ft_putstr(RED"> "WHITE);
		if (*st && *l)
			ft_putstr((*st)->name);
		fp("bl", NULL);
	}
}

static int	ctrl_r4(t_htr **t, t_struct *s, t_htr **st, char **l)
{
	sec_free(l, 0);
	if (*t)
	{
		if (!(change_lst(s, *t, 0)))
			return (1);
	}
	else if (*st)
		if (!(change_lst(s, *st, 0)))
			return (1);
	fp("ve", "cl");
	return (1);
}

static int	escape_ctrl_r(char **l)
{
	fp("ve", "cl");
	if (*l)
		free(*l);
	return (1);
}

int			ctrl_r(t_struct *s)
{
	int				ret;
	char			*l;
	char			buf[6];
	t_htr			*t;
	t_htr			*st;

	if (!s->h)
	{
		fp("bl", NULL);
		return (1);
	}
	l = NULL;
	t = s->h;
	fp("cl", "vi");
	ft_putstr("bck-i-search: _\n");
	while ((ret = read(0, &buf, 5)) && buf[0] != '\n')
	{
		if (check_char_ctrl_r(buf, ret))
			return (escape_ctrl_r(&l));
		buf[ret] = '\0';
		if (!(ctrl_r2(buf, &t, s, &l)))
			return (0);
		ctrl_r3(&l, &t, &st);
	}
	return (ctrl_r4(&t, s, &st, &l));
}
