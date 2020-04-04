/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_path_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 02:00:37 by ymarcill          #+#    #+#             */
/*   Updated: 2020/03/13 01:22:54 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"
#include <sys/mman.h>

char	*local_file(char *str)
{
	t_read	read;
	char	*dst;

	g_jobcontrol.perm = 0;
	dst = NULL;
	read.path = ft_strldup(str, '/');
	read.ptr = /*read.path ? */opendir(read.path) /*: opendir(".")*/;
	ft_strdel(&read.path);
	while (read.ptr && (read.file = readdir(read.ptr)))
	{
		read.tmp = ft_strdupn(str, '/');
	ft_putendl(read.path);
		if (read.tmp && ft_strcmp(read.tmp, read.file->d_name) == 0)
		{
			dst = ft_strdup(str);
			permissions(&dst);
			if (dst == NULL)
				g_jobcontrol.first_job->last_ret = 1;
			ft_strdel(&read.tmp);
			break ;
		}
		ft_strdel(&read.tmp);
	}
	read.ptr ? closedir(read.ptr) : 0;
	return (dst);
}

void	if_not_cmd(char *cmd)
{
	ft_putstr_fd("Shell : No cmd found: ", 2);
	ft_putendl_fd(cmd, 2);
	g_jobcontrol.ret = 1;
	g_jobcontrol.cm = 1;
}

int		check_b(char **cmd)
{
	if (cmd && cmd[0] && (!ft_strcmp(cmd[0], "jobs") || !ft_strcmp(cmd[0], "fg")
	|| !ft_strcmp(cmd[0], "bg") || !ft_strcmp(cmd[0], "setcpt")
	|| !ft_strcmp(cmd[0], "history") || !ft_strcmp(cmd[0], "help")
	|| !ft_strcmp(cmd[0], "cd") || !ft_strcmp(cmd[0], "hash") ||
	!ft_strcmp(cmd[0], "test") || !ft_strcmp(cmd[0], "exit") ||
	!ft_strcmp(cmd[0], "setenv") || !ft_strcmp(cmd[0], "unsetenv") ||
	!ft_strcmp(cmd[0], "set") || !ft_strcmp(cmd[0], "unset") ||
	!ft_strcmp(cmd[0], "export") || !ft_strcmp(cmd[0], "type") ||
	!ft_strcmp(cmd[0], "alias") || !ft_strcmp(cmd[0], "unalias") ||
	!ft_strcmp(cmd[0], "env") || !ft_strcmp(cmd[0], "echo") ||
	!ft_strcmp(cmd[0], "setclr") || !ft_strcmp(cmd[0], "cd") ||
	cmd[0][0] == '\r'))
		return (0);
	else
		return (1);
}

char	*get_hashed_mypath(t_hash *h_tab)
{
	char	*mypath;

	mypath = NULL;
	g_jobcontrol.cm = 0;
	if (h_tab && h_tab->path)
		mypath = ft_strdup(h_tab->path);
	if (mypath && permissions(&mypath))
		g_jobcontrol.ret = 1;
	return (mypath);
}

char	**set_copy(t_lst2 *menv)
{
	int     i;
	char    **dst;

	i = 0;
	if (!(dst = malloc(sizeof(char*) * ((elst_size(menv) + 1)))))
		malloc_exit();
	while (menv)
 	{
		if (menv->lcl == 1)
			dst[i++] = ft_strdup(menv->env);
		menv = menv->next;
	}
	dst[i] = NULL;
 	return (dst);
}

char	*get_set(char **tenv)
{
	char	*tmp;
	char	**env;

	env = set_copy(g_jobcontrol.s.env);
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
//	ft_putendl("iam in path");
	if (cmd && cmd[0] && check_b(cmd) == 1)
	{
	//	tmp = get_line(env);
		tmp = get_set(env);
		//ft_printtab(env);
		if (!(mypath = local_file(cmd[0])) && g_jobcontrol.perm != 1)
		{
		//	ft_putendl("CMD[0] : ");
		//	ft_putendl(cmd[0]);
		//	ft_putendl(tmp);
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
//	ft_putendl(mypath);
	return (mypath);
}
