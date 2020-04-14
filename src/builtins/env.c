#include "../../includes/projectinclude.h"

int	myenv(void)
{
	t_myenv *env;

	env = g_jobcontrol.myenv;
	while (env)
	{
		ft_putendl(env->keyval);
		env = env->next;
	}
	return (0);
}
