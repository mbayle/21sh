/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_commands_tab2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 00:22:46 by frameton          #+#    #+#             */
/*   Updated: 2020/02/16 02:16:50 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

static t_comp	*create_lst_comp_tab2(char ***del, char ***path)
{
	free_dchar(&*del);
	*path = NULL;
	return (NULL);
}

t_comp			*create_lst_comp_tab(char ***path, t_comp **bcmp, char *line,
		int i)
{
	DIR				*dir;
	struct dirent	*dir_el;
	char			**del;
	int				c;
	t_comp			*cmp;

	del = *path;
	cmp = NULL;
	c = (int)ft_strlen(line);
	while (**path)
	{
		if (!(dir = opendir(**path)))
			return (create_lst_comp_tab2(&del, &*path));
		while ((dir_el = readdir(dir)))
			if ((!(ft_strncmp(line, dir_el->
	d_name, c)) || i == 2) && !(s_command_tab(&dir_el, &cmp, &*bcmp, **path)))
				return (create_lst_comp_tab2(&del, &*path));
		if ((closedir(dir)) == -1)
			return (create_lst_comp_tab2(&del, &*path));
		(*path)++;
	}
	free_dchar(&del);
	return (cmp);
}

int				find_next_cmp(t_comp *cmp, t_comp *tmp)
{
	if (!cmp)
		return (0);
	cmp = cmp->next;
	while (cmp)
	{
		if (cmp->col == tmp->col)
			return (1);
		cmp = cmp->next;
	}
	return (0);
}

t_comp			*attribute_col(int *co, t_comp *cmp)
{
	int		j;
	int		t;
	t_comp	*bcmp;

	j = 1;
	t = 0;
	bcmp = cmp;
	while (cmp && (j < *co + 1))
	{
		cmp->col = j;
		while (cmp && t < *co)
		{
			cmp = cmp->next;
			++t;
		}
		t = 0;
		if (!cmp && (j < *co + 1))
		{
			++j;
			cmp = bcmp;
			while (cmp && cmp->col)
				cmp = cmp->next;
		}
	}
	return (cmp);
}

void			print_comp_tab(t_comp *cmp, int c, int i, int *j)
{
	while (cmp)
	{
		if (!cmp->next || cmp->next->col < cmp->col)
		{
			if (cmp->sel)
				ft_putstr(BWHITE);
			else
				check_clr(cmp);
			ft_2putstr(cmp->name, WHITE"\n");
			(*j)++;
		}
		else
		{
			if (cmp->sel)
				ft_putstr(BWHITE);
			else
				check_clr(cmp);
			ft_2putstr(cmp->name, WHITE);
			c = ft_strlen(cmp->name);
			while (c++ < i + 3)
				ft_putchar(' ');
		}
		cmp = cmp->next;
	}
}
