#include "../../includes/projectinclude.h"

int		myset(char **cmd)
{
	t_myloc	*loc;

	loc = g_jobcontrol.myloc;
	if (cmd[1])
		return (0);
	while (loc)
	{
		//printf("%p\n", loc);
		ft_putendl(loc->keyval);
		loc = loc->next;
	}
	return (0);
}
