#include "libft.h"

int		ft_is_space(char *input)
{
	int i;

	i = 0;
	while (input[i] != '\0')
	{
		if (input[i] != 32)
			return (-1);
		i++;
	}
	return (0);
}