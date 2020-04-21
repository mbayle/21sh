/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_fill_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 00:24:29 by ymarcill          #+#    #+#             */
/*   Updated: 2020/03/13 01:26:11 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

void		wait_for_job(t_process *pro, t_job *job, int fg)
{
	int			status;
	t_process	*save;
	pid_t		pid;

	save = pro;
	if (!pro)
		return ;
	pid = 0;
	while (pro && fg)
	{
		status = 0;
		if (pro->lpid > 0)
			pid = (waitpid(pro->lpid, &status, WUNTRACED));
		process_status(pro->lpid, status, pro);
		pro = pro->next;
	}
	pro = save;
	check_if_stop(pro, job);
}

t_process	*process_alloc(t_process *pro)
{
	if (!g_jobcontrol.first_job->first_process)
	{
		if ((g_jobcontrol.first_job->first_process = ft_memalloc(sizeof(
					*g_jobcontrol.first_job->first_process))) == NULL)
			malloc_exit();
		pro = g_jobcontrol.first_job->first_process;
		pro->next = NULL;
	}
	else
	{
		if (!(pro->next =
		ft_memalloc(sizeof(*g_jobcontrol.first_job->first_process))))
			malloc_exit();
		pro = pro->next;
		pro->next = NULL;
	}
	return (pro);
}

t_process	*fill_jc_struc(pid_t pid, char *cmd, t_process *pro)
{
	pro = process_alloc(pro);
	if (pid == -1)
	{
		pro->r_value = g_jobcontrol.ret + 2;
		if (g_jobcontrol.ret == 127)
			pro->r_value = 127;
	}
	pro->lpid = pid;
	pro->cmd = ft_strdup(cmd);
	if (g_jobcontrol.shell_is_int)
	{
		if (!g_jobcontrol.first_job->pgid)
		{
			if (pid > -1)
				g_jobcontrol.first_job->pgid = pid;
			else
				g_jobcontrol.first_job->pgid = g_jobcontrol.shell_pgid;
		}
		setpgid(pid, g_jobcontrol.first_job->pgid);
	}
	return (pro);
}

pid_t		last_stp_job(t_job *job)
{
	t_job	*tmp;

	tmp = job->next;
	while (job && tmp)
	{
		if (tmp && tmp->last_j >= job->last_j)
		{
			tmp = tmp->next;
			job = job->next;
		}
		else
			tmp = tmp->next;
	}
	return (job->pgid);
}

t_job		*put_last_stp(t_job *job, int i, int l)
{
	t_job	*cpy;
	t_job	*save;

	save = g_jobcontrol.first_job;
	cpy = g_jobcontrol.first_mail;
	while (cpy)
	{
		if (cpy->last_j == l && job && cpy->pgid != job->pgid)
		{
			g_jobcontrol.first_job = cpy;
			g_jobcontrol.first_job->last_j = i;
			g_jobcontrol.first_job = save;
			return (cpy);
		}
		cpy = cpy->next;
	}
	return (cpy);
}
