#include "libft.h"

int     ft_check_dquote(char *input)
{
    int     dquote;
    size_t  i;
    size_t  len;

    dquote = 0;
    i = 0;
    len = ft_strlen(input);
    while (i <= len)
    {
        if (input[i] == 92)
        {
            i = i + 2;
            continue ;
        }
        if (input[i] == 34)
        {
            if (dquote == 1)
                break ;
            else
                dquote = 1;
        }
        i++;
    }
	return (i > len ? -1 : i);
}