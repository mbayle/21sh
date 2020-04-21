/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_in_bg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 00:32:56 by ymarcill          #+#    #+#             */
/*   Updated: 2020/03/12 05:08:06 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

void	update_bg_status(void)
{
	t_job		*cpy;
	t_process	*pro;
	char		*tmp;

	cpy = g_jobcontrol.first_mail;
	while (cpy)
	{
		pro = cpy->first_process;
		browse_process(pro, cpy);
		tmp = ft_strdup(cpy->command);
		cpy = check_bg_status(cpy);
		if (cpy)
		{
			status_builtin(cpy->first_process);
			if (ft_strcmp(tmp, cpy->command) == 0)
				cpy = cpy->next;
		}
		ft_strdel(&tmp);
	}
}

t_job	**save_addr(t_job *cpy, t_job *job)
{
	t_job	*comp;
	t_job	**comp2;

	comp2 = NULL;
	while (cpy)
	{
		if (cpy->stop == 1 && job && cpy->pgid != job->pgid)
		{
			comp = cpy;
			comp2 = &comp;
		}
		cpy = cpy->next;
	}
	return (comp2);
}

int		put_last_bg(t_job *job, int i)
{
	t_job	*cpy;
	t_job	*save;
	t_job	**comp2;

	comp2 = NULL;
	save = g_jobcontrol.first_job;
	cpy = g_jobcontrol.first_mail;
	if (!job)
		return (-1);
	if (!(comp2 = save_addr(cpy, job)))
		return (-1);
	g_jobcontrol.first_job = (*comp2);
	g_jobcontrol.first_job->last_j = i;
	g_jobcontrol.first_job = save;
	return (1);
}

int		if_cont(t_job *tjob, t_job *save)
{
	if (tjob->stop != 1 && tjob->fg != 1)
	{
		ft_putstr_fd("42sh: bg: job [", 2);
		ft_putnbr_fd(tjob->j_nb, 2);
		ft_putendl_fd("] already in bg", 2);
		return (-1);
	}
	if (g_jobcontrol.first_job && g_jobcontrol.first_job->fg == 0)
		ft_putendl_fd("bg: no jobcontrol", 2);
	if (kill(-(tjob->pgid), SIGCONT) < 0)
	{
		ft_putendl_fd("Fail to continue", 2);
		return (-1);
	}
	g_jobcontrol.first_job = tjob;
	g_jobcontrol.first_job->stop = 0;
	g_jobcontrol.first_job->fg = 0;
	g_jobcontrol.first_job->last_j = 0;
	if (put_last_bg(tjob, 2) == -1)
		g_jobcontrol.first_job->last_j = 2;
	put_last_stp(put_last_stp(tjob, 1, 2), 0, 1);
	g_jobcontrol.first_job = save;
	return (0);
}

int		put_in_bg(t_job *job, int cont, char **av, t_process *pro)
{
	t_job	*save;
	t_job	*tjob;

	if (!cont)
		wait_for_job(pro, job, 0);
	tjob = right_job(cont, av, job);
	save = g_jobcontrol.first_job;
	if (cont && tjob)
	{
		if (if_cont(tjob, save) == -1)
			return (-1);
	}
	return (!tjob);
}
