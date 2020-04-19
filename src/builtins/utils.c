#include "../../includes/projectinclude.h"

void	replace_env_bis(char *keyval, char **tmp, t_myenv *env)
{
	t_myenv	*save;

	save = g_jobcontrol.myenv;
	g_jobcontrol.myenv = env;
	ft_strdel(&g_jobcontrol.myenv->keyval);
	ft_strdel(&g_jobcontrol.myenv->val);
	g_jobcontrol.myenv->keyval = ft_strdup(keyval);
	g_jobcontrol.myenv->val = ft_strdup(tmp[1]);
	g_jobcontrol.myenv = save;
}

void	replace_loc_bis(char *keyval, char **tmp, t_myloc *loc)
{
	t_myloc	*save;

	save = g_jobcontrol.myloc;
	g_jobcontrol.myloc = loc;
	ft_strdel(&g_jobcontrol.myloc->keyval);
	ft_strdel(&g_jobcontrol.myloc->val);
	g_jobcontrol.myloc->keyval = ft_strdup(keyval);
	g_jobcontrol.myloc->val = ft_strdup(tmp[1]);
	g_jobcontrol.myloc = save;
}

void	add_env_bis(char *keyval, char **tmp)
{
	g_jobcontrol.myenv->next =
		ft_memalloc(sizeof(*g_jobcontrol.myenv));
	g_jobcontrol.myenv->next->keyval =
		ft_strdup(keyval);
	g_jobcontrol.myenv->next->key =
		ft_strdup(tmp[0]);
	g_jobcontrol.myenv->next->val =
		ft_strdup(tmp[1]);
	g_jobcontrol.myenv->next->next = NULL;
}

void	add_loc_bis(char *keyval, char **tmp)
{
	g_jobcontrol.myloc->next =
		ft_memalloc(sizeof(*g_jobcontrol.myloc));
	g_jobcontrol.myloc->next->keyval =
		ft_strdup(keyval);
	g_jobcontrol.myloc->next->key =
		ft_strdup(tmp[0]);
	g_jobcontrol.myloc->next->val =
		ft_strdup(tmp[1]);
	g_jobcontrol.myloc->next->next = NULL;
}
