/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_line1_comp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 01:13:14 by frameton          #+#    #+#             */
/*   Updated: 2020/03/05 22:58:19 by frameton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

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
		if ((*path = ft_strdup("./")) == NULL)
			return (NULL);
		path[1] = NULL;
	}
	else
		path = init_tab_path(s->env_path);
	return (path);
}

int			check_prec_path(struct stat *st, char **l, char **tmp, int *ind)
{
	int		c;

	c = 0;
	if ((*l) && (*l)[c])
	{
		while ((*l)[c + 1])
			++c;
	}
	while (c && (*l)[c] != '/')
		--c;
	if (c)
		(*l)[c] = '\0';
	else
	{
		if ((*l)[0] != '/')
			return (0);
		lstat("/", &*st);
	}
	if (lstat(*l, &*st) == -1 && c)
		return (0);
	*ind = 1;
	*tmp = *l;
	if (!c && (*tmp)++)
		return (2);
	while (**tmp)
		(*tmp)++;
	(*tmp)++;
	return (1);
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
	i = check_part_comp(s, 0);
	*co = 0;
	tmp = s->l;
	while (tmp && (*co = *co + 1))
		tmp = tmp->next;
	if (!(create_line(&line, &*s, 0, *co)))
		return (0);
	if (!(path = init_list_poss2(&i, s, &*co, &sz)))
		return (sec_free(&line, 0));
	if (!(check_path_cpt(s, cmp, bcmp, &line)) && !(e_cpt(s, cmp, bcmp)))
		*cmp = create_lst_comp_tab(&path, bcmp, line, i);
	else
		free_dchar(&path);
	*bcmp = char_class_tab(*cmp, *bcmp);
	if (*bcmp)
		(*bcmp)->sel = 1;
	return (sec_free(&line, sz.ws_row));
}

int			no_match(t_struct s, t_comp *bcmp)
{
	if (bcmp && !s.cpt3)
		return (0);
	if (s.cpt3)
		return (1);
	ft_putchar('\n');
	tputs(tgetstr("up", NULL), 1, ft_ptchar);
	tputs(tgetstr("dl", NULL), 1, ft_ptchar);
	tputs(tgetstr("bl", NULL), 1, ft_ptchar);
	return (1);
}

int			edit_line_comp(t_struct *s, char buf[6], int *i)
{
	if (del_char1(buf, s, i))
		return (1);
	if ((buf[0] == 3 || buf[0] == 4) && s->ret == 1)
		return (check_sign_edl1(s, buf));
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
