/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 23:23:35 by ymarcill          #+#    #+#             */
/*   Updated: 2020/03/07 22:12:49 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

void	set_id_sign(int foreground)
{
	pid_t	pid;
	int		errno;

	errno = 0;
	pid = getpid();
	if (g_jobcontrol.first_job->pgid == 0)
		g_jobcontrol.first_job->pgid = pid;
	setpgid(pid, g_jobcontrol.first_job->pgid);
	if (foreground)
		tcsetpgrp(0, g_jobcontrol.first_job->pgid);
	ign_jb_sign(1);
}

void	fill_pipe(int oldlink[2], int newlink[2], char **av, int i)
{
	if (i > 0)
	{
		dup2(oldlink[0], 0);
		close(oldlink[0]);
	}
	if (av[i + 1])
	{
		dup2(newlink[1], 1);
		close(newlink[1]);
		close(newlink[0]);
	}
}

void	close_fd_father(int oldlink[2], int newlink[2])
{
	if (oldlink[0] > -1)
		close(oldlink[0]);
	if (newlink[1] > -1)
		close(newlink[1]);
}

char	*local_file(char *str)
{
	t_read	read;
	char	*dst;

	dst = NULL;
	read.path = ft_strldup(str, '/');
	read.ptr = read.path ? opendir(read.path) : opendir(".");
	ft_strdel(&read.path);
	while (read.ptr && (read.file = readdir(read.ptr)))
	{
		read.tmp = ft_strdupn(str, '/');
		if (read.tmp && ft_strcmp(read.tmp, read.file->d_name) == 0)
		{
			dst = ft_strdup(str);
			permissions(&dst, read.rdbuf);
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
}

int		check_b(char **cmd)
{
	if (cmd && cmd[0] && (!ft_strcmp(cmd[0], "jobs") || !ft_strcmp(cmd[0], "fg")
	|| !ft_strcmp(cmd[0], "bg") || !ft_strcmp(cmd[0], "setcpt")
	|| !ft_strcmp(cmd[0], "history") || !ft_strcmp(cmd[0], "help")
	|| !ft_strcmp(cmd[0], "cd") || !ft_strcmp(cmd[0], "echo") ||
	!ft_strcmp(cmd[0], "env") || !ft_strcmp(cmd[0], "exit") ||
	!ft_strcmp(cmd[0], "setenv") || !ft_strcmp(cmd[0], "unsetenv") ||
	!ft_strcmp(cmd[0], "set") || !ft_strcmp(cmd[0], "unset") ||
	cmd[0][0] == '\r'))
		return (0);
	else
		return (1);

}

char	*my_path(char **cmd, char **env)
{
	char	**tmp;
	char	*mypath;
	t_read	rd;

	mypath = ft_strdup("b");
	tmp = NULL;
	if (!check_b(cmd))
		return (mypath);
	else if (cmd && cmd[0])
	{
		tmp = get_line(env);
		ft_strdel(&mypath);
		if (!(mypath = local_file(cmd[0])))
		{
			mypath = get_pathh(cmd[0], tmp);
			if (mypath && permissions(&mypath, rd.rdbuf))
				g_jobcontrol.ret = 1;
			else if (!mypath && g_jobcontrol.first_job->last_ret != 1)
				if_not_cmd(cmd[0]);
		}
	}
	ft_freetab(tmp);
	return (mypath);
}
