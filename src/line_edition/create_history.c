/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 01:17:33 by frameton          #+#    #+#             */
/*   Updated: 2020/02/16 02:16:50 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

static void	create_history2(t_htr **new, char **l, t_htr **bg, t_htr **h)
{
	(*new)->next = NULL;
	(*new)->prev = NULL;
	(*new)->name = *l;
	*l = NULL;
	if (!*h && (*h = *new))
		*bg = *new;
	else
	{
		(*new)->prev = *h;
		(*h)->next = *new;
		*h = (*h)->next;
	}
}

static int	create_history3(t_struct *s)
{
	struct stat	st;

	if (lstat("./.history", &st) == -1)
	{
		s->cpt = 2;
		return (0);
	}
	return (1);
}

static int	create_history4(t_struct *s, int fd, char **l)
{
	get_next_line(fd, l);
	if (!l && (s->cpt = 2))
		return (0);
	s->cpt = (*l)[0] - 48;
	free(*l);
	get_next_line(fd, l);
	if (!l && (s->clr = 1))
		return (0);
	s->clr = ft_atoi(*l);
	free(*l);
	get_next_line(fd, l);
	if (!l && (s->ci = 1))
		return (0);
	s->ci = (*l)[0] - 48;
	free(*l);
	return (1);
}

t_htr		*create_history(t_htr *h, t_htr *new, t_htr *bg, t_struct *s)
{
	char	*l;
	int		fd;

	l = NULL;
	if (!(create_history3(s)))
		return (NULL);
	if ((fd = open("./.history", O_RDONLY)) == -1)
		return (NULL);
	if (!create_history4(s, fd, &l))
		return (NULL);
	while (get_next_line(fd, &l))
	{
		if ((new = malloc(sizeof(*new))) == NULL)
			return (NULL);
		create_history2(&new, &l, &bg, &h);
	}
	return (bg);
}
