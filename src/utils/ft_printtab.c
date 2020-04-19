#include "../../includes/projectinclude.h"

void	ft_printtab(char **tt)
{
	int	i;

	i = 0;
	while (tt && tt[i])
		ft_putendl(tt[i++]);
}
