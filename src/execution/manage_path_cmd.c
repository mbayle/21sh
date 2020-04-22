/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_path_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 02:00:37 by ymarcill          #+#    #+#             */
/*   Updated: 2020/04/22 22:30:52 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"
#include <sys/mman.h>

char	*loc2(t_read read, char *tmp, char *dst, char *str)
{
	read.path = ft_strldup(str, '/');
	read.ptr = read.path ? opendir(read.path) : opendir(".");
	while (read.ptr && (read.file = readdir(read.ptr)))
	{
		read.tmp = ft_strdupn(str, '/');
		if (read.tmp && ft_strcmp(read.tmp, read.file->d_name) == 0)
		{
			dst = ft_strdup(str);
			permissions(&dst);
			if (dst == NULL)
				g_jobcontrol.ret = 1;
			tmp = "yes";
			ft_strdel(&read.tmp);
			break ;
		}
		ft_strdel(&read.tmp);
	}
	read.ptr ? closedir(read.ptr) : 0;
	is_valid(str, tmp, read.ptr);
	ft_strdel(&read.path);
	return (dst);
}

char	*local_file(char *str)
{
	t_read	read;
	char	*dst;
	char	*tmp;

	dst = NULL;
	tmp = NULL;
	ft_bzero(&read, sizeof(read));
	g_jobcontrol.perm = 0;
	dst = loc2(read, tmp, dst, str);
	return (dst);
}

char	*get_hashed_mypath(t_hash *h_tab)
{
	char	*mypath;

	mypath = NULL;
	if (h_tab && h_tab->path)
		mypath = ft_strdup(h_tab->path);
	if (mypath && permissions(&mypath))
		g_jobcontrol.ret = 1;
	return (mypath);
}

char	*get_set(char **tenv)
{
	char	*tmp;
	char	**env;

	env = set_copy(g_jobcontrol.myloc);
	tmp = get_line(tenv);
	if (!tmp)
		tmp = get_line(env);
	ft_freetab(env);
	return (tmp);
}

char	*my_path(char **cmd, char **env)
{
	char	*tmp;
	t_hash	*h_tab;
	char	*mypath;

	mypath = NULL;
	if (cmd && cmd[0] && check_b(cmd) == 1 && cmd[0][0])
	{
		tmp = get_set(env);
		if (!(mypath = local_file(cmd[0])) && g_jobcontrol.perm != 1)
		{
			if ((h_tab = browse_command(cmd[0], tmp, &g_jobcontrol.h_tab))
			== MAP_FAILED)
			{
				if_not_cmd(cmd[0]);
				return (NULL);
			}
			mypath = get_hashed_mypath(h_tab);
			if (!mypath)
				if_not_cmd(cmd[0]);
		}
		ft_strdel(&tmp);
	}
	if (cmd && cmd[0] && !cmd[0][0])
		if_not_cmd(cmd[0]);
	return (mypath);
}
