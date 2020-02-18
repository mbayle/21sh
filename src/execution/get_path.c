#include "../../include/input.h"
#include "../../include/jobcontrol.h"
#include "../../include/sh21.h"

int		permissions(char **str, struct stat buf)
{
	int	i;

	i = 0;
	if (stat(*str, &buf) == 0 && (S_IXUSR & buf.st_mode) == 0)
	{
		ft_putstr("Minishell: Permission denied: ");
		ft_putendl(*str);
		i = 1;
		*str = NULL;
	}
	return (i);
}

char    **get_line(char **env)
{
    char    **tmp;
    char    **path;
    int     i;

    i = 0;
    tmp = NULL;
    path = NULL;
    while (env && env[i])
    {
        tmp = ft_strsplit(env[i], '=');
        if (tmp[0] && (ft_strcmp(tmp[0], "PATH")) == 0)
        {
            path = ft_strsplit(tmp[1], ':');
            ft_freetab(tmp);
            break ;
        }
        i++;
        ft_freetab(tmp);
    }
    return (path);
}

char    *get_pathh(char *nwav, char **path)
{
    int     i;
    DIR     *ptr;
    struct dirent *file;
    char    *command;

    i = -1;
    command = NULL;
    while (path && path[++i])
    {
        ptr = opendir(path[i]);
        while (ptr && (file = readdir(ptr)))
        {
            if (nwav && (ft_strcmp(file->d_name, nwav)) == 0)
            {
               command = ft_strjoin(path[i], "/");
                command = ft_strjoinnf(command, nwav);
                break ;
            }
        }
        ptr ? closedir(ptr) : 0;
    }
    return (command);
}

