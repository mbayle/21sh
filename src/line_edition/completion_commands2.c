#include "minishell.h"

int		create_line(char **line, t_struct *s, int i, int c)
{
	t_lst	*tmp;

	tmp = s->l;
	if ((*line = (char*)malloc(sizeof(*line) * (c + 1))) == NULL)
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

int		pwd_comp(struct dirent **dir_el, char *path, t_lst *l)
{
	struct stat	s;
	char		*p;
	int			c;

	p = NULL;
	c = 0;
	if (ft_strcmp("./", path))
		return (1);
	if ((p = ft_strjoin("./", (*dir_el)->d_name)) == NULL)
		return (0);
	if ((lstat(p, &s)) == -1)
		return (0);
	free(p);
	if (!(s.st_mode & S_IXGRP) && !(s.st_mode & S_IXOTH)
			&& !(s.st_mode & S_IXUSR) && !(l->prev))
		return (0);
	if (!(l->prev) && (p = ft_strjoin("./", (*dir_el)->d_name)) == NULL)
		return (0);
	else if (l->prev)
		return (1);
	while (*p)
		(*dir_el)->d_name[c++] = *p++;
	(*dir_el)->d_name[c] = '\0';
	return (1);
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
		if (!(dir = opendir(**path)))
			return (NULL);
		while ((dir_el = readdir(dir)))
			if (pwd_comp(&dir_el, **path, l) && !(ft_strncmp(line, dir_el->
							d_name, c)) && !(s_command(&dir_el, &com, &*bcom)))
				return (NULL);
		if ((closedir(dir)) == -1)
			return (NULL);
		(*path)++;
	}
	free_dchar(&del);
	return (com);
}

char	*create_line_comp(char *line, t_htr *com, t_htr *bcom, int c)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = NULL;
	if (!com->next)
		return (com->name);
	if ((tmp = ft_mstrcpy(tmp, com->name)) == NULL)
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
	while (i < c)
	{
		line[i] = tmp[i];
		++i;
	}
	line[i] = '\0';
	return (line);
}

void	check_part_comp2(t_struct *s)
{
	int		i;

	i = 0;
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
			if (s->l->next)
				s->l = s->l->next;
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
