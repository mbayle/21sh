/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 01:28:01 by ymarcill          #+#    #+#             */
/*   Updated: 2020/03/13 01:43:40 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

void	signal_print(int i)
{
	if (i == 42)
		ft_putstr_fd("SIGINT", 2);
	else if (i == 11)
		ft_putstr_fd("SIGSEGV", 2);
	else if (i == 17)
		ft_putstr_fd("SIGSTOP", 2);
	else if (i == 21)
		ft_putstr_fd("SIGTTIN", 2);
	else if (i == 22)
		ft_putstr_fd("SIGTTOU", 2);
	else if (i == 2)
		ft_putstr_fd("SIGQUIT", 2);
	else if (i == 9)
		ft_putstr_fd("SIGKILL", 2);
	else
	{
		i > 0 ? ft_putnbr_fd(i, 2) : 0;
	}
}

void	print_jc_info(t_job *job)
{
	t_process	*save1;

	save1 = job->first_process;
	while (job->first_process && job->first_process->next)
		job->first_process = job->first_process->next;
	if (job->first_process && job->first_process->status > 2
	&& job->first_process->status < 50 &&
	ft_strcmp(job->command, "fg ") && job->first_process->status != 13
	&& ft_strcmp(job->command, "exit"))
		if_stp(job, 0);
	job->first_process = save1;
}

int		process_nb(t_process *pro)
{
	int i;

	i = 0;
	while (pro && pro->next)
	{
		i++;
		pro = pro->next;
	}
	return (i);
}

void	norme(t_job *comp2, int i, t_job *save)
{
	g_jobcontrol.first_job = comp2;
	g_jobcontrol.first_job->last_j = i;
	g_jobcontrol.first_job = save;
}
