/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_comp_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 23:29:41 by frameton          #+#    #+#             */
/*   Updated: 2020/03/03 22:09:01 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

int		tab_touch(t_comp *cmp, t_comp *bcmp, int *j, int i)
{
	int		c;

	c = 0;
	del_move(4);
	tputs(tgetstr("bt", NULL), 1, ft_ptchar);
	cmp = bcmp;
	while (!cmp->sel)
		cmp = cmp->next;
	cmp->sel = 0;
	if (!cmp->next)
		bcmp->sel = 1;
	else
		cmp->next->sel = 1;
	cmp = bcmp;
	while (c < *j)
	{
		fp("up", "dl");
		++c;
	}
	*j = 0;
	print_comp_tab(cmp, 0, i, &*j);
	return (1);
}

int		entr_touch2(t_struct *s, char *line, t_lst *l)
{
	while (*line)
	{
		if ((l = malloc(sizeof(*l))) == NULL)
			return (0);
		l->c = *line++;
		l->prev = s->tmp;
		l->line = 0;
		l->plc = 0;
		l->sel = 0;
		s->tmp->next = l;
		l->next = NULL;
		s->tmp = l;
		l = NULL;
	}
	s->l = s->lbg;
	while (s->l)
	{
		ft_putchar(s->l->c);
		s->l = s->l->next;
	}
	s->l = s->lbg;
	fp("ve", NULL);
	return (1);
}

int		entr_touch(t_comp *cmp, t_struct *s, int *j, int c)
{
	char	*line;

	while (!cmp->sel)
		cmp = cmp->next;
	line = cmp->name;
	tputs(tgetstr("up", NULL), 1, ft_ptchar);
	while (c < *j - 1)
	{
		fp("up", "dl");
		++c;
	}
	fp("up", "dl");
	print_prompt_bis(s->prompt, s, 0);
	while (!s->cpt_p && s->l && line++)
		s->l = s->l->next;
	s->cpt_p = 0;
	return (entr_touch2(s, line, NULL));
}

int		select_comp_tab(t_struct *s, t_comp *cmp, int i, int j)
{
	t_comp	*bcmp;
	int		ret;
	char	buf[5];

	bcmp = cmp;
	fp("vi", NULL);
	while ((ret = read(0, &buf, 5)))
		if ((buf[0] == 9 && ret == 1) || ((buf[0] == 27 && buf[1] == 91
						&& buf[2] == 67) && ret == 3))
			tab_touch(cmp, bcmp, &j, i);
		else if (buf[0] == '\n' && ret == 1)
			return (entr_touch(cmp, s, &j, 0));
		else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 68 && ret == 3)
			left_touch(cmp, bcmp, &j, i);
		else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 65 && ret == 3)
			up_touch(cmp, bcmp, &j, i);
		else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 66 && ret == 3)
			down_touch(cmp, bcmp, &j, i);
		else
			return (other_touch(buf, &j, s));
	fp("ve", NULL);
	return (1);
}
