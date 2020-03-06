/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 23:48:54 by frameton          #+#    #+#             */
/*   Updated: 2020/02/16 02:16:50 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

static int	lst_size(t_lst *lst)
{
	int		c;

	c = 0;
	while (lst)
	{
		++c;
		lst = lst->next;
	}
	return (c);
}

static char	*init_str(t_lst *l, char *str)
{
	char	*s;

	s = str;
	while (l)
	{
		*str = l->c;
		str++;
		l = l->next;
	}
	*str = '\0';
	return (s);
}

static int	check_space(t_lst *l)
{
	while (l)
	{
		if ((l->c < 9 || l->c > 13) && l->c != 32)
			return (0);
		l = l->next;
	}
	return (1);
}

int			get_command(t_struct *s)
{
	int		i;
	char	*str;

	s->tmp = NULL;
	if ((i = (init_lst(&*s, 0, 2, 0))) == 0)
		return (0);
	if (i == 2)
		return (5);
	(*s).l = (*s).lbg;
	if (check_space((*s).l))
	{
		if (((*s).av = ft_strsplit(" ", '.')) == NULL)
			return (0);
	}
	else if ((i = lst_size((*s).l)))
	{
		if ((str = (char*)malloc(sizeof(*str) * (i + 1))) == NULL)
			return (0);
		str = init_str((*s).l, str);
		if (((*s).av = ft_splitws(str)) == NULL)
			return (0);
		free(str);
	}
	return (1);
}
