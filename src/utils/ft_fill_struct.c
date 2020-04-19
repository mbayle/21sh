#include "../../includes/projectinclude.h"

int		is_loc(char *keyval)
{
	t_myenv *env;

	env = g_jobcontrol.myenv;
	while (env)
	{
		if (ft_strcmp(env->keyval, keyval) == 0)
			return (0);
		env = env->next;
	}
	return (1);
}

void	fill_struct_env(void)
{
	t_lst2	*lst;
	t_myloc	*loc;

	loc = g_jobcontrol.myloc;
	lst = g_jobcontrol.s.env;
	while (loc)
	{
		ft_strdel(&g_jobcontrol.s.env->env);
		ft_strdel(&g_jobcontrol.s.env->varn);
		ft_strdel(&g_jobcontrol.s.env->var);
		g_jobcontrol.s.env->env = ft_strdup(loc->keyval);
		g_jobcontrol.s.env->varn = ft_strdup(loc->key);
		g_jobcontrol.s.env->var = ft_strdup(loc->val);
		g_jobcontrol.s.env->lcl = 0;
		if (is_loc(loc->keyval))
			g_jobcontrol.s.env->lcl = 1;
		if (loc->next && !g_jobcontrol.s.env->next)
		{
			g_jobcontrol.s.env->next = ft_memalloc(sizeof(*g_jobcontrol.s.env));
			g_jobcontrol.s.env->next->next = NULL;
		}
		g_jobcontrol.s.env = g_jobcontrol.s.env->next;
		loc = loc->next;
	}
	g_jobcontrol.s.env = lst;
}
