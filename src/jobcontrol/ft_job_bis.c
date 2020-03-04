#include "projectinclude.h"

void    job_error(const char *str)
{
		ft_putstr_fd("jobs: no such job : ", 2);
		ft_putendl_fd(str, 2);
}

int     job_is_completed(t_job *j)
{
		t_process   *p;

		p = j->first_process;
		while (p && p->next && p->next->next)
				p = p->next;
		if (p && (p->status >1 || p->status == -1)
		   )
				return (1);
		return (0);
}

pid_t   job_nb(int i, t_job *j)
{
		while (j->next)
		{
				if (j->j_nb == i)
						return (j->pgid);
				j = j->next;
		}
		return (0);
}

void    print_pid(t_job *j)
{
		t_process *p;

		p = j->first_process;
		while (p)
		{
				ft_putnbr_fd(p->lpid, 1);
				p = p->next;
				if (p)
						ft_putstr_fd(" | ", 1);
		}
}

