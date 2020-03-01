#include "projectinclude.h"

int     size_tab(char *line)
{
    int i;
    int nb;

    i = 0;
    nb = 0;
    while (line && line[i])
    {
        if (line[i] !=  ' ' && line[i] != '<' && line[i] != '>' && line[i] !='&')
        {
                nb++;
            while (line[i] && line[i] !=  ' ' && line[i] != '<' && line[i] != '>'
 && line[i] !='&')
                i++;
            i--;
        }
        else if (line[i] == '<' || line[i] == '>' || line[i] =='&')
        {
            nb++;
            while (line[i] == '<' || line[i]== '>' || line[i] =='&')
                i++;
            i--;
        }
        i++;
    }
    return (nb);
}

int     ft_seq_occur(char *str, char *seq)
{
    int i;
    int y;

    i = 0;
    y = 0;
    if (!str || !seq || ft_strlen(seq) > ft_strlen(str))
        return (0);
    while (str[i])
    {
        if (str[i] == seq[y])
        {
            while (str[i] && seq[y])
            {
                if (str[i++] != seq[y++])
                    return (0);
            }
            if (y == ft_strlenu(seq))
                return (1);
            else
                return (0);
        }
        i++;
    }
    return (0);
}

int     dig_to_io(char *str)
{
    int     i;
    char    *dst;

    i = 0;
    if (!(dst = ft_strnew(ft_strlen(str))))
        return (-1);
    ft_putendl(str);
    while (str[i] && ft_isdigit(str[i]))
    {
        dst[i] = str[i];
        i++;
    }
    dst[i] = '\0';
    i = ft_atoi(dst);
    ft_strdel(&dst);
    return (i);
}

int         is_strdigit(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (ft_isdigit(str[i]) == 0)
            return (0);
        i++;
    }
    return (1);
}

int     if_digit(char *file, int n)
{
        int fd;

        fd = dig_to_io(file);
        if (fcntl(fd, F_GETFD) == -1)
        {
            ft_putendl_fd("Shell: bad fd", 2);
            return (-1);
        }
        dup2(fd, n);
        return (0);
}

