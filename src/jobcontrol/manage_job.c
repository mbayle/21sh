/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_job.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 00:26:01 by ymarcill          #+#    #+#             */
/*   Updated: 2020/03/13 01:36:54 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

int		check_jb_nb(void)
{
	t_job	*first;
	int		nb;

	nb = 1;
	first = g_jobcontrol.first_mail;
	while (first)
	{
		if ((first->stop == 1 || first->fg == 0) &&
				first->pgid != g_jobcontrol.first_job->pgid)
		{
			nb = first->j_nb + 1;
		}
		first = first->next;
	}
	return (nb);
}

void	to_do_if_stp(t_job *job, t_job *save, int i)
{
	if (g_jobcontrol.first_job->pgid == job->pgid &&
	g_jobcontrol.first_job->j_nb == 0)
	{
		g_jobcontrol.repere += 1;
		g_jobcontrol.first_job->j_nb = check_jb_nb();
	}
	g_jobcontrol.first_job = job;
	g_jobcontrol.first_job->last_j = 2;
	put_last_stp(put_last_stp(job, 1, 2), 0, 1);
	if (i)
		ft_putstr_fd("\n", 2);
	ft_putstr_fd("[", 2);
	ft_putnbr_fd(g_jobcontrol.first_job->j_nb, 2);
	ft_putstr_fd("] +  ", 2);
	ft_putnbr_fd(g_jobcontrol.first_job->pgid, 2);
	if (i)
	{
		g_jobcontrol.first_job->stop = 1;
		ft_putstr_fd("  suspended ", 2);
	}
	else
		ft_putstr_fd("  running ", 2);
	ft_putendl_fd(g_jobcontrol.first_job->command, 2);
	ft_putchar_fd('\n', 2);
	g_jobcontrol.first_job = save;
}

int		check_if_stop(t_process *p, t_job *job)
{
	t_job	*save;

	save = g_jobcontrol.first_job;
	while (p)
	{
		if (p->status == 1)
		{
			to_do_if_stp(job, save, 1);
			return (1);
		}
		if (job->fg != 1)
		{
			to_do_if_stp(job, save, 0);
			return (1);
		}
		p = p->next;
	}
	return (0);
}

void	set_ret(int status)
{
	g_jobcontrol.first_job->first_process->status = status == 2 ? 42 : status;
	ft_putnbr(status);
	g_jobcontrol.first_job->first_process->r_value = status + 128;
	g_jobcontrol.ret = status + 128;
}

int		process_status(pid_t pid, int status, t_process *p)
{
	t_process *pro;

	pro = g_jobcontrol.first_job->first_process;
	if (pid < 0)
		return (-1);
	g_jobcontrol.first_job->first_process = p;
	g_jobcontrol.first_job->first_process->r_value = status;
	g_jobcontrol.ret = status;
	if (WIFEXITED(status) == TRUE)
	{
		g_jobcontrol.first_job->first_process->status = status ?50 : -1;
		g_jobcontrol.ret = WEXITSTATUS(status);
		g_jobcontrol.first_job->first_process->r_value = WEXITSTATUS(status);
	}
	else if (WIFSIGNALED(status) == TRUE)
		set_ret(status);
	else if (WIFSTOPPED(status) == TRUE)
	{
		g_jobcontrol.first_job->first_process->status = 1;
		g_jobcontrol.first_job->first_process->r_value = status;
		g_jobcontrol.ret = 128 + WSTOPSIG(status);
	}
	if (g_jobcontrol.ret == 127)
		g_jobcontrol.first_job->first_process->status = 127;
	g_jobcontrol.first_job->first_process = pro;
	return (status);
}
