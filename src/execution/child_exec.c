/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 23:23:35 by ymarcill          #+#    #+#             */
/*   Updated: 2020/03/12 02:05:07 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"
#include <sys/mman.h>

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

void	fill_pipe(int oldlink[2], int newlink[2], char ***av, int i)
{
	if (i > 0)
	{
		ft_putendl_fd("I DUP 0", 2);
		dup2(oldlink[0], 0);
		close(oldlink[0]);
	}
	if (av[i + 1])
	{
		ft_putendl_fd("I DUP 1", 2);
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
