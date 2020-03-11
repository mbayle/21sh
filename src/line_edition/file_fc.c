/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_fc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frameton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 00:49:12 by frameton          #+#    #+#             */
/*   Updated: 2020/03/10 00:49:32 by frameton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

int		rev_to_file(t_fc *f, int fd)
{
	t_list		*tmp;

	tmp = ft_lstget(f->max, g_tracking.mysh->hist->firstelement);
	while (tmp && (int)tmp->index > (f->min - 1))
	{
		ft_putendl_fd(tmp->content, fd);
		tmp = tmp->prev;
	}
	return (0);
}

int		fc_to_file(t_fc *f, int fd)
{
	t_list		*tmp;

	if (fd == -1)
		return (1);
	if (f->r == 0)
	{
		tmp = ft_lstget(f->min, g_tracking.mysh->hist->firstelement);
		while (tmp && (int)tmp->index < (f->max + 1))
		{
			ft_putendl_fd(tmp->content, fd);
			tmp = tmp->next;
		}
		return (0);
	}
	else
		return (rev_to_file(f, fd));
}

char	*fc_filename(void)
{
	char	*new;
	char	*nbr;

	new = ft_strdup("/tmp/fc");
	g_tracking.herenbr++;
	nbr = ft_itoa(g_tracking.herenbr);
	if (!nbr)
		return (NULL);
	new = ft_strjoinfree(new, nbr, 3);
	while (access(new, F_OK) != -1)
	{
		ft_strdel(&new);
		new = ft_strdup("/tmp/fc");
		g_tracking.herenbr++;
		nbr = ft_itoa(g_tracking.herenbr);
		if (!nbr)
			return (NULL);
		new = ft_strjoinfree(new, nbr, 3);
	}
	return (new);
}

int		create_fc_file(t_fc *f)
{
	char	*file;
	int		fd;

	get_neg_offset(f);
	file = NULL;
	fd = 0;
	file = fc_filename();
	if (!file)
		return (-1);
	if ((fd = open(file, O_CREAT | O_RDWR, 0777)) == -1)
		ft_putendl_fd("Couldn't create file in /tmp", 2);
	if ((fc_to_file(f, fd)) == 1)
		return (-1);
	close(fd);
	fc_edit(f, file);
	unlink(file);
	ft_strdel(&file);
	return (0);
}
