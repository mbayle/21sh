/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 00:52:43 by frameton          #+#    #+#             */
/*   Updated: 2020/03/03 22:09:01 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

void			ft_list_clear(t_gnl **begin_list, int ind)
{
	t_gnl	*src;
	t_gnl	*del;

	if (*begin_list)
	{
		src = *begin_list;
		while (src->next != NULL)
		{
			if ((*begin_list)->a == '\n')
				ind++;
			del = src;
			src = src->next;
			*begin_list = src;
			free(del);
			if (ind)
				break ;
		}
		if (!ind)
		{
			*begin_list = NULL;
			free(src);
		}
	}
}

int				ft_list_size(t_gnl *begin_list, int c)
{
	if (!c)
	{
		while (begin_list)
		{
			if (begin_list->a == '\n')
				return (1);
			begin_list = begin_list->next;
		}
		return (0);
	}
	if (!begin_list)
		return (0);
	while (begin_list->next)
	{
		begin_list = begin_list->next;
		if (begin_list->a == '\n')
			return (c);
		++c;
	}
	return (c);
}

t_gnl			*ft_lst_new(char c, t_gnl **lst, t_gnl *sa, int fd)
{
	t_gnl	*new;

	if ((new = malloc(sizeof(*new))) == NULL)
		return (0);
	new->a = c;
	new->fd = fd;
	new->next = NULL;
	if (!*lst)
	{
		*lst = new;
		(*lst)->next = NULL;
		sa = *lst;
	}
	else
	{
		(*lst)->next = new;
		*lst = (*lst)->next;
	}
	return (sa);
}

static int		ft_write(char **s, t_gnl *sa, t_gnl **lst, int j)
{
	int		c;

	if (!j && !*lst)
		return (0);
	c = 0;
	*lst = sa;
	if ((*s = (char*)malloc(sizeof(**s) * (ft_list_size(*lst, 1) + 1))) == NULL)
		return (0);
	while (sa && sa->a != '\n')
	{
		(*s)[c++] = sa->a;
		sa = sa->next;
	}
	(*s)[c] = '\0';
	ft_list_clear(&*lst, 0);
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	char			buf[BUFF_SIZE];
	int				j;
	t_gnl			*sa;
	static t_gnl	*lst;
	int				k;

	if ((read(fd, "", 0)) == -1 || !line)
		return (-1);
	sa = lst;
	while (lst && lst->next)
	{
		lst = lst->next;
		if (lst->a == '\n')
			return (ft_write(&*line, sa, &lst, 1));
	}
	while ((j = read(fd, buf, BUFF_SIZE)))
	{
		k = 0;
		while (k < j)
			sa = ft_lst_new(buf[k++], &lst, sa, fd);
		if (ft_list_size(sa, 0) == 1)
			break ;
	}
	return (ft_write(&*line, sa, &lst, j));
}
