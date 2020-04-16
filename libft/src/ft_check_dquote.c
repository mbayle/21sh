#include "libft.h"

int     ft_check_dquote(char *input)
{
    int     dquote;
    int     i;

    dquote = 0;
    i = 0;
    while (input[i])
    {
        if (input[i] == 92)
            i = i + 2;
        if (input[i] == 34)
        {
            if (dquote == 1)
                dquote = 0;
            else
                dquote = 1;
        }
        if (dquote == 0 && (input[i] == ' ' || input[i] == ';'))
            break ;
        i++;
    }
	return (i);
}