/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils2_edit_line1_comp.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 22:14:07 by frameton          #+#    #+#             */
/*   Updated: 2020/03/03 22:09:01 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

int			count_lst_comp_tab2(t_struct s)
{
	int		c;
	t_lst	*l;

	c = 0;
	l = s.lbg;
	while (l->next)
		l = l->next;
	while (l != s.lbg && check_whitespaces(l->c))
		l = l->prev;
	while (l != s.lbg && l->c != '/')
		l = l->prev;
	l = l->next;
	while (l && !check_whitespaces(l->c))
	{
		++c;
		l = l->next;
	}
	return (c);
}

int			count_lst_comp_tab(t_struct s)
{
	int		c;
	t_lst	*l;

	if (s.cpt_p2)
		return (count_lst_comp_tab2(s));
	c = 0;
	l = s.lbg;
	while (l->next)
		l = l->next;
	while (l != s.lbg && check_whitespaces(l->c))
		l = l->prev;
	while (l != s.lbg && !check_whitespaces(l->c))
		l = l->prev;
	if (check_whitespaces(l->c))
		l = l->next;
	while (l && !check_whitespaces(l->c))
	{
		++c;
		l = l->next;
	}
	return (c);
}

static int	check_path_cpt_b(t_struct *s, int ind, t_comp **bcmp)
{
	if (ind)
		s->cpt_p2 = 1;
	if (*bcmp)
		s->cpt_p = 1;
	return (1);
}

int			check_path_cpt(t_struct *s, t_comp **cmp, t_comp **bcmp, char **l)
{
	struct stat		st;
	DIR				*dir;
	struct dirent	*dir_el;
	char			*tmp;
	int				ind;

	tmp = NULL;
	ind = 0;
	if (lstat(*l, &st) == -1)
		if (!check_prec_path(&st, l, &tmp, &ind))
			return (0);
	if (!(S_ISDIR(st.st_mode)))
		return (0);
	if (!ind && check_slash(s, l))
		return (0);
	if (!(dir = opendir(*l)))
		return (0);
	while ((dir_el = readdir(dir)))
		if ((!ind && !(s_command_tab(&dir_el, &*cmp, &*bcmp, *l)))
				|| (ind && !ft_strncmp(tmp, dir_el->d_name, ft_strlen(tmp))
					&& !(s_command_tab(&dir_el, &*cmp, &*bcmp, *l))))
			return (0);
	if ((closedir(dir)) == -1)
		return (0);
	return (check_path_cpt_b(s, ind, bcmp));
}
