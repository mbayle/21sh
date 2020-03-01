#include "projectinclude.h"

void    delete_process(t_process *pro)
{
    if (!pro)
        return ;
    if (pro && pro->next)
        delete_process(pro->next);
    ft_strdel(&pro->cmd);
    ft_memdel((void**)pro);
}

void    delete_job(t_job *job)
{
    if (!job)
        return ;
    if (job->next)
        delete_job(job->next);
    delete_process(job->first_process);
    ft_strdel(&job->command);
    if (job->pgid != -1)
    {
        kill(-(job->pgid), 9);
    }
    ft_memdel((void**)job);
}

t_job   *delete_first(t_job *first)
{
    t_job   *tmp;

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

t_job   *delete_link(pid_t pgid)
{
    t_job       *first;
    t_job       *tmp;
    t_job       *save = NULL;;

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
