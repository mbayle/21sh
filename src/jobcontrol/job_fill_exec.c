#include "projectinclude.h"

void    wait_for_job(t_process *pro, t_job *job, int fg)
{
    pid_t   pid;
    int     status;
    t_process   *save;

    save = pro;
    pid = 0;
    if (!pro)
        return ;
    status = 0;
    signal(SIGCHLD, SIG_DFL);
    while (pro  && fg)
    {
        if (pro->lpid > 0)
            (waitpid(pro->lpid, &status, WUNTRACED));
        process_status(pro->lpid, status, pro);
        pro = pro->next;
    }
    pro = save;
    check_if_stop(pro, job);
}

t_process	*process_alloc(t_process *pro)
{
	if (!g_jobcontrol.first_job->first_process)
    {
        g_jobcontrol.first_job->first_process = ft_memalloc(sizeof(
*g_jobcontrol.first_job->first_process));
        pro = g_jobcontrol.first_job->first_process;
        pro->next = NULL;
    }
    else
    {
        pro->next = ft_memalloc(sizeof(*g_jobcontrol.first_job->first_process));
        pro = pro->next;
        pro->next = NULL;
    }
	return (pro);
}

t_process   *fill_jc_struc(pid_t pid, char *cmd, t_process *pro)
{
	pro = process_alloc(pro);
    if (pid == -1)
        pro->r_value = g_jobcontrol.ret;
    pro->lpid = pid;
    pro->cmd = ft_strdup(cmd);
    if (g_jobcontrol.shell_is_int)
    {
        if (!g_jobcontrol.first_job->pgid)
        {
            if (pid > -1)
                g_jobcontrol.first_job->pgid = pid;
            else
                g_jobcontrol.first_job->pgid = g_jobcontrol.shell_pgid;
        }
        setpgid(pid, g_jobcontrol.first_job->pgid);
    }
    return (pro);
}

pid_t   last_stp_job(t_job *job)
{
    t_job   *tmp;

    tmp = job->next;
    while (job &&  tmp)
    {
        if (tmp && tmp->last_j >= job->last_j)
        {
            tmp = tmp->next;
            job = job->next;
        }
        else
            tmp = tmp->next;
    }
    return (job->pgid);
}

t_job   *put_last_stp(t_job *job, int i, int l)
{
    t_job   *cpy;
    t_job   *save;

    save = g_jobcontrol.first_job;
    cpy = g_jobcontrol.first_mail;
    while (cpy)
    {
        if (cpy->last_j == l && job && cpy->pgid != job->pgid)
        {
            g_jobcontrol.first_job = cpy;
            g_jobcontrol.first_job->last_j = i;
            g_jobcontrol.first_job = save;
            return (cpy);
        }
        cpy = cpy->next;
    }
    return (cpy);
}

