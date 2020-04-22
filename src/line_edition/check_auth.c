/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_auth.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 00:25:35 by frameton          #+#    #+#             */
/*   Updated: 2020/02/16 02:16:50 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

int		check_auth(char *s)
{
	struct stat		st;

	if (lstat(s, &st) == -1)
		return (1);
	if (S_ISDIR(st.st_mode))
		return (-4);
	if (st.st_mode & S_IXUSR)
		return (2);
	else
		return (-3);
}

int		check_ls2(t_struct *s, int *n, char **tmp, struct stat *st)
{
	if (!(*s).av[0] || !(*s).av[*n] || lstat((*s).av[*n], st) == -1)
	{
		free((*s).av[1]);
		(*s).av[1] = ft_strdup(*tmp);
		ft_strdel(tmp);
		return (0);
	}
	free((*s).av[1]);
	if (tmp && ((*s).av[1] = ft_strdup(*tmp)) == NULL)
		return (0);
	ft_strdel(tmp);
	return (1);
}

int		check_ls(t_struct *s)
{
	struct stat		st;
	int				n;
	char			*tmp;

	n = 1;
	ft_strdel(&g_jobcontrol.mypath);
	tmp = ft_strdup((*s).av[1]);
	g_jobcontrol.mypath = ft_strdup((*s).av[1]);
	g_jobcontrol.p = 0;
	if ((*s).av[1] && (!ft_strcmp((*s).av[1], "-P") ||
				!ft_strcmp((*s).av[1], "-L")))
	{
		g_jobcontrol.p = 2;
		if (!ft_strcmp((*s).av[1], "-P"))
			g_jobcontrol.p = 1;
		ft_strdel(&tmp);
		if (!(*s).av[2])
		{
			ft_strdel(&(*s).av[1]);
			return (0);
		}
		tmp = ft_strdup((*s).av[2]);
		n = 2;
	}
	return (check_ls2(s, &n, &tmp, &st));
}
