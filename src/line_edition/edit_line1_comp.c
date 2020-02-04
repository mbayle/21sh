/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_line1_comp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frameton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 01:13:14 by frameton          #+#    #+#             */
/*   Updated: 2020/02/03 23:39:24 by frameton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_part_comp(t_struct *s)
{
	if (check_whitespaces(s->l->c))
		return (0);
	while (s->l->next && !(check_whitespaces(s->l->next->c)))
		s->l = s->l->next;
	if (!(s->l->next))
	{
		s->l = s->lbg;
		return (1);
	}
	else
	{
		while (s->l && s->l->next)
			s->l = s->l->next;
		if (check_whitespaces(s->l->c))
		{
			s->l = s->l->next;
			return (2);
		}
		else
		{
			while (!(check_whitespaces(s->l->prev->c)))
				s->l = s->l->prev;
			return (3);
		}
	}
}

static char	**init_list_poss2(int *i, t_struct *s, int *co,
		struct winsize *sz)
{
	char	**path;

	ioctl(0, TIOCGWINSZ, &*sz);
	*co = (*sz).ws_col;
	if (*i == 2 || *i == 3)
	{
		if ((path = (char**)malloc(sizeof(*path) * 2)) == NULL)
			return (NULL);
		if ((*path = ft_mstrcpy(*path, "./")) == NULL)
			return (NULL);
		path[1] = NULL;
	}
	else
		path = init_tab_path(s->env_path);
	return (path);
}

int			init_list_poss(t_struct *s, int *co, t_comp **cmp, t_comp **bcmp)
{
	struct winsize	sz;
	char			*line;
	int				i;
	char			**path;
	t_lst			*tmp;

	line = NULL;
	s->l = s->lbg;
	i = check_part_comp(s);
	*co = 0;
	tmp = s->l;
	while (tmp)
	{
		tmp = tmp->next;
		(*co)++;
	}
	if (!(create_line(&line, &*s, 0, *co)))
		return (0);
	if (!(path = init_list_poss2(&i, s, &*co, &sz)))
		return (sec_free(&line, 0));
	*cmp = create_lst_comp_tab(&path, bcmp, line, i);
	*bcmp = char_class_tab(*cmp, *bcmp);
	if (*bcmp)
		(*bcmp)->sel = 1;
	return (sec_free(&line, sz.ws_row));
}

int			no_match(t_struct s, t_comp *bcmp)
{
	(void)s;
	if (bcmp && !s.cpt3)
		return (0);
	ft_putchar('\n');
	tputs(tgetstr("up", NULL), 1, ft_ptchar);
	tputs(tgetstr("dl", NULL), 1, ft_ptchar);
	tputs(tgetstr("bl", NULL), 1, ft_ptchar);
	return (1);
}

int			edit_line_comp(t_struct *s, char buf[5], int *i)
{
	if (del_char(buf, s, i))
		return (1);
	if (buf[0] == 9)
	{
		if (!s->comp.name && s->lbg)
			return (show_list_poss(s));
		if (s->comp.name)
		{
			if (s->comp.name)
				s->comp.name = NULL;
			return (1);
		}
		return (ft_completion(&*s, NULL, buf, 1));
	}
	return (4);
}
