#include "projectinclude.h"

t_job       *if_bg_stp(t_job *job, t_job *save)
{
    while (job)
    {
        if (job->pgid == last_stp_job(save))
            break;
        job = job->next;
    }
    return (job);
}

t_job       *if_bg(t_job *job, t_job *save, char *av)
{
    t_job   *comp;
    t_job   **tmp;

	tmp = NULL;
    if (ft_strcmp(av, "bg") == 0)
    {
        while (job)
        {
            if (job->stop == 1)
            {
                comp = job;
                tmp = &comp;
            }
            job = job->next;
        }
        job = tmp ? (*tmp) : if_bg_stp(job, save);
    }
    else
        job = if_bg_stp(job, save);
    return (job);
}

t_job       *if_parser(char **av, t_job *job)
{
    pid_t   pgid;
    pgid = av[1][0] != '%' ? jobs_parser(av[1], job) :
                 job_nb(ft_atoi(av[1] + 1), job);
    if (pgid == 0)
        ft_putendl_fd("Error no job", 2);
    while (pgid && job->next)
    {
        if (job->pgid == pgid)
            break;
        job = job->next;
    }
    return (job);
}

t_job       *stopped_pgid(char **av, t_job *job)
{
    t_job   *save;

    save = job;
    if ((av && !av[1]) || !av)
        job = if_bg(job, save, av[0]);
    else if (!av[2])
        job = if_parser(av, job);
    if (job && (job->stop == 1 || (job->stop != 1 &&
                                    job->fg != 1)))
        return (job);
    else
        return (NULL);
}

