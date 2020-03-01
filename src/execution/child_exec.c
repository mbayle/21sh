#include "projectinclude.h"
#include "../includes/jobcontrol.h"
void    set_id_sign(int foreground)
{
    pid_t   pid;
    int     errno;

    errno = 0;
    pid = getpid();
    if (g_jobcontrol.first_job->pgid == 0)
       g_jobcontrol.first_job->pgid = pid;
    setpgid(pid, g_jobcontrol.first_job->pgid);
    if (foreground)
    {
        tcsetpgrp(0, g_jobcontrol.first_job->pgid);
//  ft_putendl("DAN LA COND");
    }
    ign_jb_sign(1);
}

void    fill_pipe(int oldlink[2], int newlink[2], char **av, int i)
{
    if (i > 0)
    {
        dup2(oldlink[0], 0);
        close(oldlink[0]);
    }
    if (av[i + 1])
    {
        dup2(newlink[1], 1);
        close(newlink[1]);
        close(newlink[0]);
    }
}
void    close_fd_father(int oldlink[2], int newlink[2])
{
    if (oldlink[0] > -1)
        close (oldlink[0]);
    if (newlink[1] > -1)
        close(newlink[1]);
}



char    *local_file(char *str)
{
    t_read  read;
    char    *dst;

    dst = NULL;
    read.path = ft_strldup(str, '/');
    read.ptr = read.path ? opendir(read.path) : opendir(".");
    ft_strdel(&read.path);
    while (read.ptr && (read.file = readdir(read.ptr)))
    {
        read.tmp = ft_strdupn(str, '/');
        if (read.tmp && ft_strcmp(read.tmp, read.file->d_name) == 0
)
        {
            dst = ft_strdup(str);
            permissions(&dst, read.rdbuf);
            ft_strdel(&read.tmp);
            break;
        }
        ft_strdel(&read.tmp);
    }
    read.ptr ? closedir(read.ptr) : 0;
    return (dst);
}

char        *my_path(char **cmd, char **env)
{
    char    **tmp;
    char    *mypath;

    mypath = ft_strdup("b");
    tmp = NULL;
    if (ft_strcmp(cmd[0], "jobs") == 0 || ft_strcmp(cmd[0], "fg") == 0
        || ft_strcmp(cmd[0], "bg") == 0|| cmd[0][0] == '\r')
        return (mypath);
    else
    {
        tmp = get_line(env);
        ft_strdel(&mypath);
        if (!(mypath = local_file(cmd[0])))
        {
            mypath = get_pathh(cmd[0], tmp);
            if (!mypath)
            {
                ft_putstr_fd("Shell : No cmd found: ", 2);
                ft_putendl_fd(cmd[0], 2);
                g_jobcontrol.ret = -1;
            }
        }
    }
    ft_freetab(tmp);
    return (mypath);
}


