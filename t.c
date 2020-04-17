#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

static char    *ft_mstrcpy(char *dest, const char *src)
{
        char    *sa;
        int             c;

        c = 0;
        while (src[c])
                c++;
        if ((dest = (char*)malloc(sizeof(*dest) * (c + 1))) == NULL)
                return (NULL);
        sa = dest;
        while (*src)
                *dest++ = *src++;
        *dest = '\0';
        return (sa);
}

int main()
{
	char **tab;

	tab = (char**)malloc(sizeof(*tab) * 3);
	tab[0] = ft_mstrcpy(NULL, "test");
	tab[1] = ft_mstrcpy(NULL, "Test2");
	tab[2] = NULL;
	return (0);
}
