#include "../../includes/projectinclude.h"

int	check_loc(char *keyval)
{
	char	**tmp;
	t_myloc *loc;

	loc = g_jobcontrol.myloc;
	tmp = ft_strsplit(keyval, '=');
	while (loc)
	{
		if (ft_strcmp(loc->key, tmp[0]) == 0)
		{
			ft_freetab(tmp);
			return (0);
		}
		loc = loc->next;
	}
	ft_freetab(tmp);
	return (1);
}

int	replace_loc(char *keyval)
{
	char	**tmp;
	t_myloc	*loc;
	t_myloc	*save;

	loc = g_jobcontrol.myloc;
	save = g_jobcontrol.myloc;
	tmp = ft_strsplit(keyval, '=');
	if (!check_env(keyval))
		replace_env(keyval, 0);
	while (loc)
	{
		if (ft_strcmp(loc->key, tmp[0]) == 0)
		{
			replace_loc_bis(keyval, tmp, loc);
			ft_freetab(tmp);
			return (0);
		}
		loc = loc->next;
	}
	return (1);
}

int	add_loc(char *keyval)
{
	char	**tmp;
	t_myloc	*loc;

	loc = g_jobcontrol.myloc;
	tmp = ft_strsplit(keyval, '=');
	while (g_jobcontrol.myloc)
	{
		if (!g_jobcontrol.myloc->next)
		{
			add_loc_bis(keyval, tmp);
			ft_freetab(tmp);
			break ;
		}
		g_jobcontrol.myloc = g_jobcontrol.myloc->next;
	}
	g_jobcontrol.myloc = loc;
	return (0);
}

int	setloc(char **cmd)
{
	int	i;
	int ret;

	i = 0;
	ret = 0;
	if (!cmd)
		return (0);
	while (cmd[i])
	{
		if (check_error(cmd[i]))
			return (1);
		if (!check_loc(cmd[i]))
			ret = replace_loc(cmd[i]);
		else
			ret = add_loc(cmd[i]);
		if (ret)
			return (ret);
		i++;
	}
	return (ret);
}
