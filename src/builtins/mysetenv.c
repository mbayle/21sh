#include "../../includes/projectinclude.h"

int	check_error(char *keyval)
{
	if (ft_occur(keyval, '=') > 1 || !ft_occur(keyval, '='))
	{
		ft_putendl_fd("Set / Setenv : invalid param", 2);
		return (1);
	}
	return (0);
}

int	check_env(char *keyval)
{
	char	**tmp;
	t_myenv *env;

	env = g_jobcontrol.myenv;
	tmp = ft_strsplit(keyval, '=');
	if (ft_strcmp(tmp[0], "PATH") == 0)
		hash_reset(&g_jobcontrol.h_tab);
	while (env)
	{
		if (ft_strcmp(env->key, tmp[0]) == 0)
		{
	//		ft_putendl("checkenv env->key: ");
	//		ft_putendl(env->key);
			ft_freetab(tmp);
			return (0);
		}
		env = env->next;
	}
	ft_freetab(tmp);
	return (1);
}

int	replace_env(char *keyval, int ass)
{
	char	**tmp;
	t_myenv	*env;
	t_myenv	*save;

	env = g_jobcontrol.myenv;
	save = g_jobcontrol.myenv;
	tmp = ft_strsplit(keyval, '=');
	while (env)
	{
		if (ft_strcmp(env->key, tmp[0]) == 0)
		{
			g_jobcontrol.myenv = env;
			ft_strdel(&g_jobcontrol.myenv->keyval);
			ft_strdel(&g_jobcontrol.myenv->val);
			g_jobcontrol.myenv->keyval = ft_strdup(keyval);
			g_jobcontrol.myenv->val = ft_strdup(tmp[1]);
			ft_freetab(tmp);
			g_jobcontrol.myenv = save;
			ass ? replace_loc(keyval) : 0;
			return (0);
		}
		env = env->next;
	}
	ass ? replace_loc(keyval) : 0;
	ft_freetab(tmp);
	return (1);
}

int	add_env(char *keyval, int ass)
{
	char	**tmp;
	t_myenv	*env;

	env  = g_jobcontrol.myenv;
	tmp = ft_strsplit(keyval, '=');
	while (g_jobcontrol.myenv)
	{
		if (!g_jobcontrol.myenv->next)
		{
			g_jobcontrol.myenv->next =
				ft_memalloc(sizeof(*g_jobcontrol.myenv));
			g_jobcontrol.myenv->next->keyval =
				ft_strdup(keyval);
			g_jobcontrol.myenv->next->key =
				ft_strdup(tmp[0]);
			g_jobcontrol.myenv->next->val =
				ft_strdup(tmp[1]);
			ft_freetab(tmp);
			g_jobcontrol.myenv->next->next = NULL;
			break ;
		}
		g_jobcontrol.myenv = g_jobcontrol.myenv->next;
	}
	g_jobcontrol.myenv = env;
	if (ass)
	{
		if (replace_loc(keyval))
			add_loc(keyval);
	}
	return (0);

}

int	mysetenv(char **cmd, int ass)
{
	int	i;
	int ret;

	i = 1;
	ret = 0;
	if (!cmd)
		return (1);
	while (cmd[i])
	{
		if (check_error(cmd[i]))
			return (1);
		if (!check_env(cmd[i]))
			ret = replace_env(cmd[i], ass);
		else
			ret = add_env(cmd[i], ass);
		if (ret)
			return (ret);
		i++;
	}
	return (ret);

}
