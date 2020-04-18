/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   changed_status.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 00:14:55 by ymarcill          #+#    #+#             */
/*   Updated: 2020/03/25 01:03:22 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

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
//		ft_putstr_fd("	", 2);
	}
}

void	if_stp(t_job *job, int i)
{
	if (i)
	{
		ft_putchar_fd('[', 2);
		ft_putnbr_fd(job->j_nb, 2);
		ft_putstr_fd("]+	", 2);
	}
//	else
	ft_putstr_fd("[", 2);
	ft_putnbr_fd(job->pgid, 2);
	ft_putstr_fd("] ", 2);
	if (i && job->first_process->status <= 0)
		ft_putstr_fd(" Done", 2);
	else
		ft_putstr_fd(" Terminated ", 2);
	signal_print(job->first_process->status);
	ft_putstr_fd(":	", 2);
	ft_putstr_fd(job->command, 2);
	ft_putchar_fd('\n', 2);
	put_last_fg(put_last_stp(job, 2, 1), 1, 0);
}

t_job	*print_and_del(t_job *job, int i, int check)
{
	t_job		*save;
	t_process	*save1;

	save = job;
	if (i != 0 && i == check)
	{
		if (job->stop == 1 || job->fg == 0)
			if_stp(job, 1);
		save = delete_link(job->pgid);
		if (!save && g_jobcontrol.first_mail)
			save = job;
	}
	else if (job && job->fg == 1 && job->stop != 1)
	{
//		ft_putendl(job->command);	
		save1 = job->first_process;
		while (job->first_process && job->first_process->next)
				job->first_process = job->first_process->next;
		if (job->first_process && job->first_process->status > 2
		&& job->first_process->status < 50 &&
		ft_strcmp(job->command, "fg ") && job->first_process->status != 13
		&& ft_strcmp(job->command, "exit"))
			if_stp(job, 0);
		job->first_process = save1;
		save = delete_link(job->pgid);
		if (!save && g_jobcontrol.first_mail)
			save = job;
	}
	return (save);
}

t_job	*check_bg_status(t_job *job)
{
	int			check;
	int			i;
	t_process	*p;

	i = 0;
	check = 0;
	p = job->first_process;
	while (p)
	{
		i++;
		if ((job->fg == 0 || job->stop == 1) && (p->status > 1
			|| p->status == -1))
			check++;
		p = p->next;
	}
	job = print_and_del(job, i, check);
	return (job);
}

void	status_builtin(t_process *pro)
{
	t_process *p;

	p = pro;
//	printf("%s %p\n", "ADDR de pro", pro);	
//	return ; // IF PIPE CRASH
	while (pro && p)
	{
		if (p && p->lpid < 0)
			p->status = p->r_value;
		p = p->next;
	}
}

void	browse_process(t_process *pro, t_job *cpy)
{
	int		status;
//	int		b_pid;
	pid_t	pid;

	status = 0;
	pid = 0;
//	b_pid = 0;
	while (pro)
	{
//		b_pid = pro->lpid;
		if (pro->lpid > 0)
		{
			pid = waitpid(pro->lpid, &status, WUNTRACED
					| WNOHANG);
			if (pro && pro->lpid == pid)
			{
				process_status(pid, status, pro);
				if (pro->status == 1)
					check_if_stop(pro, cpy);
				break ;
			}
		}
		pro = pro->next;
	}
}
