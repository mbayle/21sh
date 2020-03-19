#include "../../includes/projectinclude.h"

void		malloc_exit(void)
{
	ft_putendl_fd("Malloc fail, leaving the shell", 2);
	exit_edl(&g_jobcontrol.s, NULL);
}
