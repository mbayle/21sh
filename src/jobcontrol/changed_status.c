#include "projectinclude.h"

void    if_stp(t_job *job)
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
        if (job->first_process->status > 2 )
            ft_putnbr_fd(job->first_process->status, 2)
;
        ft_putchar_fd('\n', 2);
        put_last_fg(put_last_stp(job, 2, 1), 1, 0);
    }
}

t_job   *print_and_del(t_job *job, int i, int check)
{
    t_job   *save;

    save = job;
    if (i != 0 && i == check)
    {
        if_stp(job);
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

t_job   *check_bg_status(t_job *job)
{
    t_process   *p;
    int         check;
    int         i;

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

void    status_builtin(t_process *pro)
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

void    browse_process(t_process *pro, t_job *cpy)
{
    int     status;
    int     b_pid;
    pid_t   pid;

    status = 0;
    pid = 0;
    while (pro)
    {
        b_pid = pro->lpid;
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
