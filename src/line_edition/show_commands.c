/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 23:31:10 by frameton          #+#    #+#             */
/*   Updated: 2020/02/16 02:16:50 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

t_htr		*char_class(t_htr *l, t_htr *s)
{
	char	*tmp;

	l = s;
	tmp = NULL;
	while (l && l->next)
	{
		if ((ft_strcmp(l->name, l->next->name)) > 0)
		{
			tmp = l->name;
			l->name = l->next->name;
			l->next->name = tmp;
			if (l->prev)
				l = l->prev;
		}
		else
			l = l->next;
	}
	return (s);
}

void		free_completion_commands(t_htr **del, int i)
{
	t_htr	*tmp;

	while ((tmp = *del))
	{
		*del = (*del)->next;
		free(tmp->name);
		free(tmp);
	}
	if (i > 1)
		ft_putchar('\n');
}

int			s_command3(t_htr **l, t_htr **bg, struct dirent **dir_el)
{
	if ((*l = malloc(sizeof(**l))) == NULL)
		return (0);
	if (((*l)->name = ft_strdup((*dir_el)->d_name)) == NULL)
		return (0);
	(*l)->next = NULL;
	(*l)->prev = NULL;
	*bg = *l;
	return (1);
}

static int	check_cpt_exist(t_htr *bg, struct dirent *dir_el)
{
	t_htr	*tmp;

	tmp = bg;
	if (!bg)
		return (0);
	while (tmp)
	{
		if (!(ft_strcmp(tmp->name, dir_el->d_name)))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int			s_command(struct dirent **dir_el, t_htr **l, t_htr **bg)
{
	if (check_cpt_exist(*bg, *dir_el))
		return (1);
	if (!*l)
	{
		if (!(s_command3(&*l, &*bg, &*dir_el)))
			return (0);
	}
	else
	{
		if (((*l)->next = malloc(sizeof(**l))) == NULL)
			return (0);
		if (((*l)->next->name = ft_strdup((*dir_el)->d_name)) == NULL)
			return (0);
		(*l)->next->next = NULL;
		(*l)->next->prev = *l;
		*l = (*l)->next;
	}
	return (1);
}
