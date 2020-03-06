/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_commands_tab.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 23:30:48 by frameton          #+#    #+#             */
/*   Updated: 2020/02/16 02:16:50 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

t_comp		*char_class_tab(t_comp *l, t_comp *s)
{
	char	*tmp;
	int		clr;

	l = s;
	while (l && l->next)
		if ((ft_strcmp(l->name, l->next->name)) > 0)
		{
			tmp = l->name;
			clr = l->clr;
			l->name = l->next->name;
			l->clr = l->next->clr;
			l->next->name = tmp;
			l->next->clr = clr;
			if (l->prev)
				l = l->prev;
		}
		else
			l = l->next;
	l = s;
	while (l)
	{
		l->sel = 0;
		l = l->next;
	}
	return (s);
}

static int	s_command3_tab(t_comp **l, t_comp **bg, struct dirent **dir_el)
{
	if ((*l = malloc(sizeof(**l))) == NULL)
		return (0);
	if (((*l)->name = ft_mstrcpy((*l)->name, (*dir_el)->d_name)) == NULL)
		return (0);
	(*l)->next = NULL;
	(*l)->prev = NULL;
	(*l)->col = 0;
	(*l)->sel = 0;
	*bg = *l;
	return (1);
}

int			s_command_tab(struct dirent **dir_el, t_comp **l, t_comp **bg,
		char *p)
{
	if (!*l)
	{
		if (!(s_command3_tab(&*l, &*bg, &*dir_el)))
			return (0);
	}
	else
	{
		if (((*l)->next = malloc(sizeof(**l))) == NULL)
			return (0);
		if (((*l)->next->name = ft_mstrcpy((*l)->next->name
						, (*dir_el)->d_name)) == NULL)
			return (0);
		(*l)->next->next = NULL;
		(*l)->next->prev = *l;
		(*l)->col = 0;
		(*l)->sel = 0;
		*l = (*l)->next;
	}
	(*l)->clr = clr_cmp(*l, p);
	return (1);
}
