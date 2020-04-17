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
			g_jobcontrol.myloc = loc;
			ft_strdel(&g_jobcontrol.myloc->keyval);
			ft_strdel(&g_jobcontrol.myloc->val);
			g_jobcontrol.myloc->keyval = ft_strdup(keyval);
			g_jobcontrol.myloc->val = ft_strdup(tmp[1]);
			ft_freetab(tmp);
			g_jobcontrol.myloc = save;
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

	loc  = g_jobcontrol.myloc;
	tmp = ft_strsplit(keyval, '=');
	while (g_jobcontrol.myloc)
	{
		if (!g_jobcontrol.myloc->next)
		{
			g_jobcontrol.myloc->next =
					ft_memalloc(sizeof(*g_jobcontrol.myloc));
			g_jobcontrol.myloc->next->keyval =
					ft_strdup(keyval);
			g_jobcontrol.myloc->next->key =
					ft_strdup(tmp[0]);
			g_jobcontrol.myloc->next->val =
					ft_strdup(tmp[1]);
			ft_freetab(tmp);
			g_jobcontrol.myloc->next->next = NULL;
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
