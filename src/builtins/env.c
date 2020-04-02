#include "../../includes/projectinclude.h"

int		print_env(void)
{
	t_lst2	*menv;

	menv = g_jobcontrol.s.env;
	while (menv)
	{
		if (menv->lcl == 0)
			ft_putendl(menv->env);
		menv = menv->next;
	}
	return (1);
}

int		ft_env(char	**cmd)
{
	if (!cmd[1])
		return (print_env());
	if (ft_strcmp(cmd[1], "-i") == 0)
		ft_freetab(g_jobcontrol.env);
	if (cmd[2])
	{
	}
}
