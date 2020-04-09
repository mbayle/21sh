/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils_edit_line1_comp.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 00:25:14 by frameton          #+#    #+#             */
/*   Updated: 2020/03/08 21:51:29 by frameton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

int				free_bcmp_tab(t_comp **bcmp, t_comp **cmp, int i)
{
	t_comp	*del;

	del = NULL;
	while (*bcmp)
	{
		del = (*bcmp)->next;
		free((*bcmp)->name);
		free(*bcmp);
		*bcmp = del;
	}
	*bcmp = NULL;
	*cmp = NULL;
	return (i);
}

static void		show_list_poss3(t_comp **cmp, int *i, int *co, t_comp **bcmp)
{
	while (*cmp)
	{
		if ((int)ft_strlen((*cmp)->name) > *i)
			*i = ft_strlen((*cmp)->name);
		*cmp = (*cmp)->next;
	}
	*cmp = *bcmp;
	*co = (*co / (*i + 3));
	*cmp = attribute_col(&*co, *cmp);
	*cmp = *bcmp;
}

static int		show_list_poss2(t_struct *s, t_comp **cmp, int row, int *co)
{
	int		i;
	int		j;
	int		size;
	t_comp	*bcmp;

	i = 0;
	j = 0;
	size = 0;
	bcmp = *cmp;
	show_list_poss3(&*cmp, &i, &*co, &bcmp);
	print_comp_tab(*cmp, 0, i, &j);
	*cmp = bcmp;
	while (*cmp)
	{
		if ((*cmp)->col == 1)
			++size;
		*cmp = (*cmp)->next;
	}
	if (size > row - 1)
		return (free_bcmp_tab(&bcmp, cmp, 1));
	fp("vi", NULL);
	if (!(select_comp_tab(s, bcmp, i, j)))
		return (free_bcmp_tab(&bcmp, &*cmp, -1));
	fp("ve", NULL);
	return (free_bcmp_tab(&bcmp, &*cmp, 1));
}

static int		comp_lv1(t_struct *s, t_comp **cmp, t_comp **bcmp)
{
	t_lst	*tmp;
	int		c;

	c = count_lst_comp_tab(*s);
	tmp = NULL;
	while ((*cmp)->name[c])
	{
		if ((tmp = malloc(sizeof(*tmp))) == NULL)
			return (free_bcmp_tab(bcmp, cmp, 0));
		tmp->c = (*cmp)->name[c++];
		tmp->sel = 0;
		tmp->next = NULL;
		tmp->prev = s->tmp;
		s->tmp->next = tmp;
		s->tmp = s->tmp->next;
	}
	return (free_bcmp_tab(bcmp, cmp, 1));
}

int				show_list_poss(t_struct *s)
{
	t_comp	*cmp;
	t_comp	*bcmp;
	int		co;
//	int		j;
	int		row;

//	j = 0;
	co = 0;
	cmp = NULL;
	bcmp = NULL;
	if (!(row = init_list_poss(s, &co, &cmp, &bcmp)))
		return (free_bcmp_tab(&bcmp, &cmp, 0));
	if (no_match(*s, bcmp))
		return (free_bcmp_tab(&bcmp, &cmp, 1));
	if ((!bcmp->next && s->cpt == 1) || (!bcmp->next && s->cpt > 1
				&& !s->comp.name))
		return (comp_lv1(s, &cmp, &bcmp));
	if (!bcmp->next && s->cpt > 1)
		return (free_bcmp_tab(&bcmp, &cmp, 1));
	if (bcmp)
		ft_putchar('\n');
	tputs(tgetstr("sc", NULL), 1, ft_ptchar);
	cmp = bcmp;
	return (show_list_poss2(s, &cmp, row, &co));
}
