#include "../../include/input.h"
#include "../../include/jobcontrol.h"
#include "../../include/sh21.h"

void    ft_freetab(char **s1)
{
    int i;

    i = 0;
    while (s1 && s1[i])
    {
        free(s1[i]);
        s1[i] = NULL;
        i++;
    }
    free(s1);
    s1 = NULL;
}

