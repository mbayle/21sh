#include "projectinclude.h"

int         dup_fd(char *redir, char *file)
{
    int n;

    n = dig_to_io(redir);
    if (n == 0)
        n = redir[0] == '>' ? 1: 0;
    if (fcntl(n, F_GETFD) == -1)
    {
        ft_putendl_fd("Shell: bad fd", 2);
        return (-1);
    }
    if (!ft_strcmp(file, "-"))
        close(n);
    else if (is_strdigit(file))
    {
        if ((if_digit(file,  n)) == -1)
            return (-1);
    }
    else
    {
        ft_putendl_fd("Shell: ambuguous redirect", 2);
        return (-1);
    }
    return (0);

}


int     out_err_redir(char *file)
{
    int fd;

    fd = 0;
    if (!ft_strcmp(file, "-"))
    {
        if (close(1) == -1 || close(2) == -1)
            fd = -1;
        g_jobcontrol.ret = fd;
        return (fd);
    }
    if (access(file, F_OK) == -1)
    {
        if ((fd = open(file, O_CREAT, 0644)) < 0)
        {
            write(2, "Failure : error while creating the file", 39);
            return (-1);
        }
    }
    fd = open(file, O_WRONLY | O_TRUNC);
    dup2(fd, 2);
    dup2(fd, 1);
    close(fd);
    return (0);
}


int     redir_to_file(char **cmd, int i, int ret)
{

    if (ft_seq_occur(cmd[i], "&>"))
        ret = out_err_redir(cmd[i + 1]);
    else if (ft_seq_occur(cmd[i], ">"))
        ret = redirect_to_file(cmd[i], cmd[i + 1], O_TRUNC, 1);
    return (ret);
}

int     execute_redir(char **cmd)
{
    int i;
    int ret;

    i = 0;
    ret = -1;
    while (cmd[i])
    {
        if (ft_seq_occur(cmd[i], ">>"))
            ret =  redirect_to_file(cmd[i], cmd[i + 1], O_APPEND, 1);
        else if (ft_seq_occur(cmd[i], "<<"))
            ft_putendl("O \"<<\" has occur");
//          redirect_to_file(cmd[i], cmd[i + 1], O_APPEND, 1);
        else if (ft_seq_occur(cmd[i], "&>") || ft_seq_occur(cmd[i], ">"))
            ret  = redir_to_file(cmd, i, ret);
        else if (ft_seq_occur(cmd[i], ">&"))
            ret = dup_fd(cmd[i], cmd[i + 1]);
        else if (ft_seq_occur(cmd[i], "<&"))
            ret = dup_fd(cmd[i], cmd[i + 1]);
        else if (ft_seq_occur(cmd[i], "<"))
            ret = redirect_to_file(cmd[i], cmd[i + 1], O_RDONLY, 0);
        if (ret == -1)
            return (-1);
        i++;
    }
    return (0);
}

