/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion_commands.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 01:14:00 by frameton          #+#    #+#             */
/*   Updated: 2020/02/16 02:16:50 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

void		free_bcom(t_struct *s)
{
	t_htr	*del;

	del = NULL;
	while (s->bcom)
	{
		del = s->bcom->next;
		free(s->bcom->name);
		free(s->bcom);
		s->bcom = del;
	}
	s->com = NULL;
	s->bcom = NULL;
}

int			putchar_completion2(t_struct *s, char c)
{
	t_lst	*l;

	l = NULL;
	if ((l = malloc(sizeof(*l))) == NULL)
		return (0);
	l->c = c;
	l->next = NULL;
	l->prev = s->tmp;
	l->line = 0;
	l->plc = 0;
	l->sel = 0;
	s->tmp->next = l;
	s->tmp = s->tmp->next;
	return (1);
}

int			completion_commands(char ***path, int c, t_struct *s, int i)
{
	char		*line;
	t_lst		*tmp;
	char		**del;

	(void)i;
	s->l = s->lbg;
	del = *path;
	if (!(check_whitespaces(s->tmp->c)))
		check_part_comp2(&*s, 0);
	tmp = s->l;
	while (s->l && (c = c + 1))
		s->l = s->l->next;
	s->l = tmp;
	if (!c)
		return (free_path(&del, 1));
	if (!(create_line(&line, &*s, 0, c)))
		return (-1);
	if (!(s->com = create_lst_comp(&*path, &s->bcom, line, s->l)))
		return (sec_free(&line, -1));
	s->bcom = char_class(s->bcom, s->bcom);
	s->l = s->lbg;
	if ((s->bcom->next && s->cpt == 2) || (s->bcom->next && s->cpt == 4))
		return (sec_free(&line, 1));
	return (putchar_completion(&*s, &s->bcom, &line, c));
}

int			ft_completion(t_struct *s, char **path, char buf[6], int i)
{
	char	*line;
	int		c;

	line = NULL;
	c = 0;
	if (s->env_i && !(path = init_tab_path2(s->env_path, s)))
		return (-1);
	if (s->env_i && i == 2 && s->lbg && (s->l = s->lbg))
	{
		while (s->l && (c = c + 1))
			s->l = s->l->next;
		s->l = s->lbg;
		if (!(create_line(&line, s, 0, c)))
			return (sec_free(&line, free_path(&path, -1)));
		s->com = create_lst_comp(&path, &s->bcom, line, s->l);
		s->bcom = char_class(s->bcom, s->bcom);
		return (sec_free(&line, 1));
	}
	else if (s->env_i && !s->lbg && !s->tmp && buf[0] == 9 && i)
		return (show_commands(&path, 0, NULL, NULL));
	else if (s->env_i && s->lbg && !s->tmp->next && s->cpt > 1)
		return (completion_commands(&path, 0, &*s, 0));
	if (s->env_i && buf[0] == 9)
		return (free_path(&path, 3));
	return (free_path(&path, 1));
}
