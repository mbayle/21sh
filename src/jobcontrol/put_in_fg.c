#include "projectinclude.h"

t_job		*stopped_pgid(char **av, t_job *job)
{
	pid_t	pgid;
	t_job	*save;

	save = job;
	if ((av && !av[1]) || !av)
	{
		
		while (job)
		{
			if (job->pgid == last_stp_job(save))
				break ;;
			job = job->next;
		}
	}
	else if (!av[2])
	{
		pgid = av[1][0] != '%' ? jobs_parser(av[1], job) : job_nb(ft_atoi(av[1] + 1), job);
		if (pgid == 0)
			ft_putendl_fd("Error no job", 2);
		while (pgid && job->next)
		{
			if (job->pgid == pgid)
				break;
			job = job->next;
		}
	}
	ft_putnbr(job->pgid);
	if (job && (job->stop == 1 || (job->stop != 1 && job->fg != 1)))
		return (job);
	else
		return (NULL);
}

void		change_stop_flag()
{
	
}

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

t_job		*right_job(int cont, char **av, t_job *job)
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

void	put_last_fg(t_job *job, int i, int l)
{
	t_job   *cpy;
	t_job   *save;
	t_job	*comp;
	t_job	**comp2;

	comp = NULL;
	comp2 = NULL;
	save = g_jobcontrol.first_job;
	cpy = g_jobcontrol.first_mail;
	if (job)
	{
		ft_putnbr(i);
		ft_putnbr(l);
		ft_putstr("MA FG VAL :");
		ft_putendl(job->command);
		ft_putnbr(job->last_j);
	}
	if (!job)
		return ;
	while (cpy)
	{
		ft_putstr("IN FG LOOP : ");
		ft_putnbr(cpy->last_j);
		ft_putendl(cpy->command);
   	 	if ((cpy->stop == 1 || cpy->fg != 1) && cpy->last_j == l && job && cpy->pgid != job->pgid)
		{
			ft_putstr("FG VAL :");
			ft_putendl(cpy->command);
			comp = cpy;
			comp2 = &comp;
		}
    	cpy = cpy->next;
	}
	if (!comp2)
		return ;
    g_jobcontrol.first_job = (*comp2);
    g_jobcontrol.first_job->last_j = i;
   	g_jobcontrol.first_job = save;
}

int		put_in_fg(int cont, t_job *job, char **av)
{
	t_job	*save;
	t_job	*tjob;
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
		tcsetpgrp(0, tjob->pgid);
//		reset_attr();
		ft_putendl_fd(tjob->command, 2);
//		init_shell_sig();
//		ign_jb_sign(1);
		tcsetattr(0, TCSANOW, &g_jobcontrol.save_attr);
		if (kill(-(tjob->pgid), SIGCONT) < 0)
		{
			ft_putendl_fd("Fail to continue", 2);
			return (1);
		}
		ft_putstr_fd("JOB VAL :", 2);
		ft_putendl(tjob->command);
		g_jobcontrol.first_job = tjob;
		g_jobcontrol.first_job->stop = -1;
		g_jobcontrol.first_job->last_j = 0;
		g_jobcontrol.first_job->fg = 1;
		put_last_fg(put_last_stp(tjob, 2, 1), 1, 0);
		g_jobcontrol.first_job = save;
		pro = tjob->first_process;
		save = tjob;
//		exit(0);
	}
	wait_for_job(pro, save, 1);
	tcsetpgrp(0, g_jobcontrol.shell_pgid);
	//init_shell_sig();
//	tcgetattr(0, &tjob->j_mode);
	tcsetattr(0, TCSANOW, &g_jobcontrol.term_attr);
	return (!tjob);
}
