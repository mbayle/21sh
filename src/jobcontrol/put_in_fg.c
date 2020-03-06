/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_in_fg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 00:34:34 by ymarcill          #+#    #+#             */
/*   Updated: 2020/03/07 00:38:14 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

int		fg_or_bg(pid_t pgid, t_job *job)
{
	t_job	*save;

	save = job;
	while (save)
	{
		if (save->pgid == pgid)
			return (save->fg);
		save = save->next;
	}
	return (-1);
}

t_job	*right_job(int cont, char **av, t_job *job)
{
	t_job	*tjob;

	if (cont)
	{
		tjob = stopped_pgid(av, job);
		if (tjob == NULL)
		{
			ft_putstr_fd(av[0], 2);
			if (av[0] && av[1] && av[2])
				ft_putendl_fd(": Too many arguments", 2);
			else
				ft_putendl_fd(": no current job", 2);
		}
	}
	else
		tjob = g_jobcontrol.first_job;
	return (tjob);
}

void	norme(t_job *comp2, int i, t_job *save)
{
	g_jobcontrol.first_job = comp2;
	g_jobcontrol.first_job->last_j = i;
	g_jobcontrol.first_job = save;
}

void	put_last_fg(t_job *job, int i, int l)
{
	t_job	*cpy;
	t_job	*save;
	t_job	*comp;
	t_job	**comp2;

	comp = NULL;
	comp2 = NULL;
	save = g_jobcontrol.first_job;
	cpy = g_jobcontrol.first_mail;
	if (!job)
		return ;
	while (cpy)
	{
		if ((cpy->stop == 1 || cpy->fg != 1) && cpy->last_j == l && job &&
				cpy->pgid != job->pgid)
		{
			comp = cpy;
			comp2 = &comp;
		}
		cpy = cpy->next;
	}
	if (!comp2)
		return ;
	norme((*comp2), i, save);
}

int		if_fg_cont(t_job *tjob, t_job *save)
{
	tcsetpgrp(0, tjob->pgid);
	ft_putendl_fd(tjob->command, 2);
	tcsetattr(0, TCSANOW, &g_jobcontrol.save_attr);
	if (kill(-(tjob->pgid), SIGCONT) < 0)
	{
		ft_putendl_fd("Fail to continue", 2);
		return (-1);
	}
	g_jobcontrol.first_job = tjob;
	g_jobcontrol.first_job->stop = -1;
	g_jobcontrol.first_job->last_j = 0;
	g_jobcontrol.first_job->fg = 1;
	put_last_fg(put_last_stp(tjob, 2, 1), 1, 0);
	g_jobcontrol.first_job = save;
	return (0);
}

int		put_in_fg(int cont, t_job *job, char **av)
{
	t_job		*save;
	t_job		*tjob;
	t_process	*pro;

	save = g_jobcontrol.first_job;
	pro = g_jobcontrol.first_job->first_process;
	tjob = right_job(cont, av, job);
	if (tjob == NULL)
		tcsetpgrp(0, g_jobcontrol.first_job->pgid);
	if (g_jobcontrol.first_job && g_jobcontrol.first_job->fg == 0)
		ft_putendl_fd("fg: no jobcontrol", 2);
	if (cont && tjob)
	{
		if (if_fg_cont(tjob, save) == -1)
			return (-1);
		pro = tjob->first_process;
		save = tjob;
	}
	wait_for_job(pro, save, 1);
	tcsetpgrp(0, g_jobcontrol.shell_pgid);
	tcsetattr(0, TCSANOW, &g_jobcontrol.term_attr);
	return (!tjob);
}
