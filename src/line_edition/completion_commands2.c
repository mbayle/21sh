/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion_commands2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 01:17:04 by frameton          #+#    #+#             */
/*   Updated: 2020/03/09 11:36:40 by frameton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

int		create_line(char **line, t_struct *s, int i, int c)
{
	t_lst	*tmp;

	tmp = s->l;
	if ((*line = (char*)malloc(sizeof(**line) * (c + 1))) == NULL)
		return (0);
	while (s->l)
	{
		(*line)[i++] = s->l->c;
		s->l = s->l->next;
	}
	(*line)[i] = '\0';
	s->l = tmp;
	return (1);
}

int		pwd_comp(struct dirent **dir_el, char *path, t_lst *l, int c)
{
	struct stat	s;
	char		*p;
	char		*del;

	p = NULL;
	if (ft_strcmp("./", path))
		return (1);
	if ((p = ft_strjoin("./", (*dir_el)->d_name)) == NULL)
		return (0);
	if ((lstat(p, &s)) == -1)
		return (sec_free(&p, 0));
	sec_free(&p, 0);
	if (!(s.st_mode & S_IXGRP) && !(s.st_mode & S_IXOTH)
			&& !(s.st_mode & S_IXUSR) && !(l->prev))
		return (0);
	if (!(l->prev) && (p = ft_strjoin("./", (*dir_el)->d_name)) == NULL)
		return (0);
	else if (l->prev)
		return (sec_free(&p, 1));
	del = p;
	while (*p)
		(*dir_el)->d_name[c++] = *p++;
	(*dir_el)->d_name[c] = '\0';
	return (sec_free(&del, 1));
}

t_htr	*create_lst_comp(char ***path, t_htr **bcom, char *line, t_lst *l)
{
	DIR				*dir;
	struct dirent	*dir_el;
	char			**del;
	int				c;
	t_htr			*com;

	del = *path;
	com = NULL;
	c = (int)ft_strlen(line);
	while (**path)
	{
		while (!(dir = opendir(**path)))
			(*path)++;
		if (!**path)
			break ;
		while ((dir_el = readdir(dir)))
			if (pwd_comp(&dir_el, **path, l, 0) && !(ft_strncmp(line, dir_el->
							d_name, c)) && !(s_command(&dir_el, &com, &*bcom)))
				return (create_lst_comp2(&del, path));
		if ((closedir(dir)) == -1)
			return (create_lst_comp2(&del, path));
		(*path)++;
	}
	free_dchar(&del);
	return (com);
}

char	*create_line_comp(char **line, t_htr *com, t_htr *bcom, int c)
{
	char	*tmp;
	int		i;

	i = 0;
	if (!com->next && (sec_free(line, 1)))
		return (*line = ft_mstrcpy(NULL, com->name));
	if ((tmp = ft_mstrcpy(NULL, com->name)) == NULL)
		return (NULL);
	while (1)
	{
		while (com && !(strncmp(tmp, com->name, c + 1)))
			com = com->next;
		if (!com && (com = bcom))
			++c;
		else
			break ;
	}
	sec_free(line, 0);
	if ((*line = (char*)malloc(sizeof(**line) * c + 1)) == NULL)
		return (NULL);
	while (i < c && (i = i + 1))
		(*line)[i - 1] = tmp[i - 1];
	(*line)[i] = '\0';
	sec_free(&tmp, 0);
	return (*line);
}

void	check_part_comp2(t_struct *s, int i)
{
	while (1)
	{
		if (check_whitespaces(s->l->c) && (i = 1))
		{
			while (s->l && check_whitespaces(s->l->c))
				s->l = s->l->next;
			if (!s->l)
				i = 0;
		}
		else
		{
			if (s->l->next)
				s->l = s->l->next;
		}
		if (!s->l->next && !i && (s->l = s->lbg))
			break ;
		if (!s->l->next && i)
		{
			while (s->l && !(check_whitespaces(s->l->c)))
				s->l = s->l->prev;
			s->l = s->l->next;
			break ;
		}
	}
}
