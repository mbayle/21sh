#include "projectinclude.h"

void	delete_process(t_process *pro)
{
	if (!pro)
		return ;
	if (pro && pro->next)
		delete_process(pro->next);
	ft_strdel(&pro->cmd);
	ft_memdel((void**)pro);
}

void	delete_job(t_job *job)
{
	if (!job)
		return ;
	if (job->next)
		delete_job(job->next);
//	ft_putendl("im here in dele");
	delete_process(job->first_process);
	ft_strdel(&job->command);
	ft_memdel((void**)job);
}
	
t_job	*delete_first(t_job *first)
{
	t_job	*tmp;

//	ft_putstr("The first command is : ");
//	ft_putendl(first->command);
//	ft_putnbr(first->pgid);
	delete_process(first->first_process);
	ft_strdel(&first->command);
	tmp = first;
	first = first->next;
	ft_memdel((void**)tmp);
	ft_memdel((void**)&g_jobcontrol.first_mail);
	if (first)
		g_jobcontrol.first_mail = first;
	else
		g_jobcontrol.first_job = NULL;
	return (first);
}

t_job	*delete_link(pid_t pgid)
{
	t_job 		*first;
	t_job		*tmp;
	t_job		*save = NULL;;

	first = g_jobcontrol.first_mail;
	if (first->pgid == pgid)
		return (delete_first(first));
	while (first && first->next)
	{
		if (first->next->pgid == pgid)
		{
			save = first;
			ft_strdel(&first->next->command);
			delete_process(first->next->first_process);
			tmp  = first->next;
			if (first->next->next == NULL)
				g_jobcontrol.first_job = first;
			first->next = first->next->next;
			ft_memdel((void**)tmp);
			break ;
		}
		first = first->next;
	}
	return (NULL);
}

t_job	*print_and_del(t_job *job, int i, int check)
{
	t_job	*save;

	save = job;
	if (i != 0 && i == check)
	{
		if (job->stop == 1 || job->fg ==0)
		{
			ft_putchar_fd('[', 2);
			ft_putnbr_fd(job->j_nb, 2);
			ft_putstr_fd("]  ", 2);
			ft_putnbr_fd(job->pgid, 2);
			ft_putchar_fd(' ', 2);
			ft_putstr_fd(job->command, 2);
			ft_putstr_fd("  Terminated ", 2);
			if (job->first_process->status > 2 )//&& job->first_process->status != 0 )
				ft_putnbr_fd(job->first_process->status, 2);
			ft_putchar_fd('\n', 2);
		}
		save = delete_link(job->pgid);
		if (!save && g_jobcontrol.first_mail)
			save = job;
	}
	else if (job->fg == 1 && job->stop != 1)
	{
		save = delete_link(job->pgid);
		if (!save && g_jobcontrol.first_mail)
			save = job;
	}
	return (save);
}

t_job	*check_bg_status(t_job *job)
{
	t_process 	*p;
	int			check;
	int			i;

	i = 0;
	check = 0;
	p = job->first_process;
	while (p)
	{
		i++;
		if ((job->fg == 0 || job->stop == 1) && (p->status > 1 || p->status == -1))
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
	while (p)
	{
		if (p->lpid < 0)
			p->status = p->r_value;
		p = p->next;
	}
}

void	update_bg_status()
{
	int			status = 0;
	int			b_pid;
	pid_t		pid  = 0;
	t_job		*cpy;
	t_process	*pro;
	t_job		*check = NULL;

check = NULL;	
	cpy = g_jobcontrol.first_mail;;
	while (cpy)
	{
		pro = cpy->first_process;
		while (pro)
		{
			b_pid = pro->lpid;
///			ft_putendl(pro->cmd);
//			ft_putnbr(pro->lpid);
			if (pro->lpid > 0)
			{
				pid = waitpid(pro->lpid, &status, WUNTRACED | WNOHANG);
	//			ft_putendl("TO KNOW");
	//			ft_putnbr(status);
	//			ft_putnbr(pid);
	//			ft_putnbr(pro->lpid);
				if (pro && pro->lpid == pid)
				{
					process_status(pid, status, pro);
					if (pro->status == 1)
				//	if (cpy->stop == 1)
						check_if_stop(pro, cpy);
					break ;
				}
			}
			pro = pro->next;
		}
		cpy = check_bg_status(cpy);
		if (cpy)
		{
			status_builtin(cpy->first_process);
			cpy = cpy->next;
		}
	}
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
		if (g_jobcontrol.first_job && g_jobcontrol.first_job->fg == 0)
			ft_putendl_fd("bg: no jobcontrol", 2);
		if (kill(-(tjob->pgid), SIGCONT) < 0)
		{
			ft_putendl_fd("Fail to continue", 2);
			return (1);
		}
		g_jobcontrol.first_job = tjob;
		g_jobcontrol.first_job->stop = 0;
		g_jobcontrol.first_job->fg = 0;
		g_jobcontrol.first_job->last_j = 2;
		put_last_stp(put_last_stp(tjob, 1, 2), 0, 1);
		g_jobcontrol.first_job  = save;
	}
		return (!tjob);
}
