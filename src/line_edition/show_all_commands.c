/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_all_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 23:29:26 by frameton          #+#    #+#             */
/*   Updated: 2020/03/03 22:09:01 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

static t_htr	*char_lst_class(t_htr *l, t_htr *s, char ***del)
{
	char	*tmp;

	ft_putchar('\n');
	l = s;
	tmp = NULL;
	free_dchar(&*del);
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

static void		free_all_commands(t_htr **del, int i)
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

static int		show_command3(int w, int c, int co, t_htr **bg)
{
	int				i;
	struct winsize	sz;
	t_htr			*del;

	del = *bg;
	ioctl(0, TIOCGWINSZ, &sz);
	w = sz.ws_col / (c + 3);
	i = 1;
	while (*bg)
	{
		if (i == w && (i = 1))
			ft_putendl((*bg)->name);
		else
		{
			ft_putstr((*bg)->name);
			co = ft_strlen((*bg)->name);
			while (co++ < (c + 2))
				tputs(tgetstr("nd", NULL), 1, ft_ptchar);
			co = 0;
			++i;
		}
		*bg = (*bg)->next;
	}
	free_all_commands(&del, i);
	return (3);
}

static int		show2(struct dirent **dir_el, size_t *c, t_htr **l, t_htr **bg)
{
	if ((ft_strlen((*dir_el)->d_name)) > *c)
		*c = ft_strlen((*dir_el)->d_name);
	if (!*l)
	{
		if ((*l = malloc(sizeof(**l))) == NULL)
			return (0);
		if (((*l)->name = ft_mstrcpy((*l)->name, (*dir_el)->d_name)) == NULL)
			return (0);
		(*l)->next = NULL;
		(*l)->prev = NULL;
		*bg = *l;
	}
	else
	{
		if (((*l)->next = malloc(sizeof(**l))) == NULL)
			return (0);
		if (((*l)->next->name = ft_mstrcpy((*l)->name
		, (*dir_el)->d_name)) == NULL)
			return (0);
		(*l)->next->next = NULL;
		(*l)->next->prev = *l;
		*l = (*l)->next;
	}
	return (1);
}

int				show_commands(char ***path, size_t c, t_htr *l, t_htr *bg)
{
	DIR				*dir;
	struct dirent	*dir_el;
	char			**del;

	del = *path;
	while (**path)
	{
		if (!(dir = opendir(**path)))
		{
			ft_eputstr("Error opendir: bad access path.\n");
			return (-1);
		}
		while ((dir_el = readdir(dir)))
			if (!(show2(&dir_el, &c, &l, &bg)))
				return (-1);
		if ((closedir(dir)) == -1)
		{
			ft_eputstr("Error: failed closedir process.\n");
			return (-1);
		}
		if ((*path)++ && **path && !(ft_strcmp("./", **path)))
			(*path)++;
	}
	bg = char_lst_class(bg, bg, &del);
	return (show_command3(0, c, 0, &bg));
}
