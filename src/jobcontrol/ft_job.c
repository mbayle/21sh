#include "projectinclude.h"

pid_t       jobs_parser(char *str, t_job *j)
{
	int     i;
	pid_t   pgid;

	i = 0;
	pgid = 0;
	while (j->next)
	{
		ft_putendl_fd(j->command, 1);
		if (((j->fg == 0 && !job_is_completed(j)) ||
			j->stop == 1) && ft_strcmp(j->command, str) == 0)
			return (j->pgid);
		else if (((j->fg == 0 && !job_is_completed(j)) ||
				j->stop == 1) && j->command[i] == str[i])
		{
			while (str[i] && str[i] == j->command[i])
				i++;
			if (i == ft_strlenu(str))
				pgid = j->pgid;
			i = 0;
		}
		j = j->next;
	}
	return (pgid);
}

void    print_job_status(int i, t_job *j, t_job *f_job)
{
		pid_t   pgid;

		ft_putnbr(j->last_ret);
		if (j->last_ret == 149 || j->last_ret == 150)
				return ;
		pgid = last_stp_job(f_job);
		ft_putstr_fd("[", 1);
		ft_putnbr_fd(j->j_nb, 1);
		ft_putstr_fd("]  ", 1);
		print_pid(j);
		ft_putchar(' ');
		if (pgid && pgid == j->pgid)
				ft_putstr_fd(" +", 1);
		else
				ft_putstr_fd("  ", 1);
		if (i == 1)
				ft_putstr_fd(" suspended ", 1);
		else
				ft_putstr_fd(" running ", 1);
		ft_putendl_fd(j->command, 1);
}

void    no_param_jobs(t_job *j)
{
		t_job   *save;

		save = j;
		while (j)
		{
				if (j->stop == 1)
						print_job_status(j->stop, j, save);
				else if (j->fg != 1 && !job_is_completed(j))
						print_job_status(j->stop, j, save);
				j = j->next;
		}
}

void	job_param(char **av, t_job *j)
{
	int		i;
	pid_t	pgid;
	t_job	*save;

	i = 0;
	pgid = 0;
	save = j;
	while (av[i])
	{
		pgid = av[i][0] != '%' ? jobs_parser(av[i], save) :
			job_nb(ft_atoi(av[i] + 1), save);
		if (pgid == 0)
			return (job_error(av[i]));
		ft_putnbr_fd(pgid, 1);
		while (pgid && j->next)
		{
			if (j->pgid == pgid)
				print_job_status(j->stop, j, save);
			j = j->next;
		}
		i++;
		j = save;
	}
}

int     ft_jobs(t_job *j, char **av)
{
		int     i;
		pid_t   pgid;
		t_job   *save;

		i = 1;
		save = j;
		pgid = 0;
		if (g_jobcontrol.first_job && g_jobcontrol.first_job->fg == 0)
				return (2);
		if (!av[1])
				no_param_jobs(j);
		else
			job_param(av, j);
		return (2);
}

