/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frameton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 19:38:03 by frameton          #+#    #+#             */
/*   Updated: 2020/02/24 23:25:56 by frameton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

int			set_p_ac(char **p, char *av, t_struct2 *st)
{
//	int		size;

	*p = av;
	st->name = av;
//	size = ft_strlen(*p);
	if ((*p)[0] != '/' && ft_strncmp(*p, "./", 2) && ft_strncmp(*p, "../", 3))
		if ((*p = ft_strjoin("./", *p)) == NULL)
			return (-1);
	return (1);
}

static void	init_s(t_struct2 *s, char **p)
{
	s->cmd = *p;
	s->exs = 1;
	s->reg = 0;
	s->dir = 0;
	s->chr = 0;
	s->blk = 0;
	s->fifo = 0;
	s->lnk = 0;
	s->sock = 0;
	s->suid = 0;
	s->sgid = 0;
	s->stick = 0;
	s->rd = 0;
	s->wrt = 0;
	s->exc = 0;
	s->sz = 0;
}

static void	set_s2(t_struct2 *st, struct stat s)
{
	s.st_mode & S_ISUID ? st->suid = 1 : 0;
	s.st_mode & S_ISGID ? st->sgid = 1 : 0;
	s.st_mode & S_ISVTX ? st->stick = 1 : 0;
	st->sz = s.st_size;
}

void		set_s(t_struct2 *st, struct stat s, char **p)
{
	init_s(st, p);
	if (S_ISREG(s.st_mode))
		st->reg = 1;
	if (S_ISDIR(s.st_mode))
		st->dir = 1;
	if (S_ISCHR(s.st_mode))
		st->chr = 1;
	if (S_ISBLK(s.st_mode))
		st->blk = 1;
	if (S_ISFIFO(s.st_mode))
		st->fifo = 1;
	if (S_ISLNK(s.st_mode))
		st->lnk = 1;
	if (S_ISSOCK(s.st_mode))
		st->sock = 1;
	s.st_mode & S_IRUSR ? st->rd = 1 : 0;
	s.st_mode & S_IRGRP ? st->rd = 1 : 0;
	s.st_mode & S_IROTH ? st->rd = 1 : 0;
	s.st_mode & S_IWUSR ? st->wrt = 1 : 0;
	s.st_mode & S_IWGRP ? st->wrt = 1 : 0;
	s.st_mode & S_IWOTH ? st->wrt = 1 : 0;
	s.st_mode & S_IXUSR ? st->exc = 1 : 0;
	s.st_mode & S_IXGRP ? st->exc = 1 : 0;
	s.st_mode & S_IXOTH ? st->exc = 1 : 0;
	set_s2(st, s);
}
