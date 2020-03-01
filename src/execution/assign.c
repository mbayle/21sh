#include "projectinclude.h"

int     tab_size(char **s)
{
    int i;

    i = 0;
    while (s && s[i])
        i++;
    return (i);
}

char    **tab_copy(char **tabl)
{
    int     i;
    int     j;
    char    **dst;

    i = 0;
    j = 0;
    if (!(dst = malloc(sizeof(char *) * (tab_size(tabl) + 1))))
        return (NULL);
    while (tabl[i])
    {
        dst[j] = ft_strdup(tabl[i++]);
        j++;
    }
    dst[j] = NULL;
    return (dst);
}

char    **del_one(char **tabl, int pos)
{
    int     i;
    int     j;
    char    **dst;

    i = 0;
    j = 0;
    if (!(dst = malloc(sizeof(char*) * (tab_size(tabl) + 1))))
        return (NULL);
    while (tabl[i])
    {
        if (i == pos)
            i++;
        if (tabl[i])
            dst[j++] = ft_strdup(tabl[i++]);

    }
    dst[j] = NULL;
    ft_putendl(dst[0]);
    ft_freetab(tabl);
    return (dst);

}

char    **check_assign(char **ass)
{
    char    *tmp;
    int     i;

    i = 0;
    tmp = NULL;
    while (ass[i])
    {
        if (ass[i][0] == '\r')
        {
            tmp = ft_strdup(ass[i]);
            free(ass[i]);
            ft_putstr("check assign : ");
            ft_putendl(tmp + 1);
            ass[i] = ft_strdup(tmp + 1);
            if (i == 0)
            {
                //g_jobcontrol.ret= ft_export.c();
                ass = del_one(ass, 0);
            }
        }
        i++;
    }
    return (ass);
}

