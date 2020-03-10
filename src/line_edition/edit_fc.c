/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_fc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frameton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 00:47:48 by frameton          #+#    #+#             */
/*   Updated: 2020/03/10 00:48:03 by frameton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

t_lstcontainer		*init_fc(char *path)
{
	int				fd;
	t_lstcontainer	*fc_lst;
	char			*fc;

	fc_lst = NULL;
	fd = open(path, O_RDWR, 0777);
	fc = NULL;
	if (fd == -1)
	{
		ft_putendl_fd("Failed to load fc file", 2);
		ft_putstr(path);
		ft_strdel(&path);
		return (NULL);
	}
	fc_lst = lstcontainer_new();
	while (get_next_line(fd, &fc) != 0)
		lstcontainer_add(fc_lst, fc);
	return (fc_lst);
}

void				fc_loop(char *path)
{
	t_lstcontainer	*fc_lst;
	t_list			*tmp;
	char			*line;

	if (!path)
		return (ft_putendl("failed to /tmp/fc"));
	tcsetattr(0, TCSANOW, &g_tracking.default_term);
	fc_lst = init_fc(path);
	if (!fc_lst)
		return ;
	tmp = fc_lst->firstelement;
	while (tmp)
	{
		line = ft_strdup(tmp->content);
		if (g_tracking.interactive == 1 && g_tracking.linemode == 0)
			ft_putchar_fd('\n', 0);
		while (check_eol(line) != 0)
			line = end_line(line);
		ft_putendl(line);
		main_loop(line);
		tmp = clean_jobs_next_tmp(line, tmp);
	}
	ft_lstdel(fc_lst->firstelement, 1);
	ft_free(fc_lst);
	ft_strdel(&path);
}

void				fc_edit(t_fc *f, char *path)
{
	char			*edit;

	if (f->edtr == NULL)
	{
		if (!g_tracking.mysh || !g_tracking.mysh->set_env)
			edit = ft_strdup("ed");
		else
			edit = ft_strdup(get_set_env_string("FCEDIT"));
		if (!edit)
			edit = ft_strdup("ed");
	}
	else
		edit = ft_strdup(f->edtr);
	edit = ft_strjoinfree(edit, " ", 1);
	edit = ft_strjoinfree(edit, path, 1);
	main_loop(edit);
	fc_loop(ft_strdup(path));
	ft_strdel(&edit);
}
