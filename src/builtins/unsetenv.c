#include "../../includes/projectinclude.h"

int	delete_env_first(t_myenv *env)
{
	t_myenv	*save;

	ft_strdel(&env->next->key);
	ft_strdel(&env->next->val);
	ft_strdel(&env->next->keyval);
	save = env;
	env = env->next;
	ft_memdel((void**)&save);
	if (env)
		g_jobcontrol.myenv = env;
	else
		g_jobcontrol.myenv = NULL;
	return (0);
}

int	delete_env(char *keyval)
{
	char	**tmp;
	t_myenv *env;
	t_myenv *save;

	tmp = ft_strsplit(keyval, '=');
	env = g_jobcontrol.myenv;
	if (!ft_strcmp(env->key, tmp[0]))
		delete_env_first(env);
	while (env)
	{
		if (env->next && !ft_strcmp(env->next->key, tmp[0]))
		{
			ft_strdel(&env->next->key);
			ft_strdel(&env->next->val);
			ft_strdel(&env->next->keyval);
			save = env->next;
			env->next = env->next->next;
			ft_memdel((void**)&save);
			ft_freetab(tmp);
			return (0);
		}
		env = env->next;
	}
	ft_freetab(tmp);
	return (1);
}

int	myunsetenv(char **cmd)
{
	int	i;

	i = 1;
	while (cmd[i])
	{
		delete_env(cmd[i]);
		delete_loc(cmd[i]);
		i++;	
	}
	return (0);
}
