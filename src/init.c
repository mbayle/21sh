/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 16:05:51 by ymarcill          #+#    #+#             */
/*   Updated: 2020/04/22 16:13:56 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

static void	init_term(t_struct *s)
{
	s->env_i = 1;
	tgetent(NULL, getenv("TERM"));
	s->prompt = 0;
	s->cpt3 = 0;
	s->copy = 0;
	s->eq = 0;
	s->cpt5 = 0;
	s->edq = 0;
	s->cpt_p3 = 0;
	s->cpt_p = 0;
	s->b = 0;
	s->p = 0;
	s->bs = 0;
	s->cpt_p2 = 0;
	s->exit = 0;
	s->ctrl_d = 0;
	s->cmd = NULL;
	s->cpcl = NULL;
	s->env = NULL;
	s->l = NULL;
	s->tmp = NULL;
	s->lbg = NULL;
}

void		init_struct(t_struct *s, char **envp)
{
	char	**save;

	init_term(s);
	(*s).h = NULL;
	(*s).first = 0;
	s->set_cpt = 0;
	(*s).comp.name = NULL;
	s->bcom = NULL;
	s->com = NULL;
	save = envp;
	if (((*s).builtin_ref = init_builtin_ref(0)) == NULL)
		ft_exit(0, &*s);
	if (!*envp)
		(*s).env = NULL;
	else if (((*s).env = init_lst_env(NULL, envp, NULL, 0)) == NULL)
		ft_exit(0, &*s);
	envp = save;
	init_start_pwd(s);
	if (((*s).env_path = search_pathenv((*s).env)) == NULL)
		ft_eputstr("42sh "MAGENTA"warning"
		WHITE": the PATH environment variable does not exist.\n\0");
}

void		init_myenv(char **envp)
{
	int		i;
	t_myenv	*save;
	char	**tmp;

	i = 0;
	g_jobcontrol.myenv = ft_memalloc(sizeof(*g_jobcontrol.myenv));
	g_jobcontrol.myenv->next = NULL;
	save = g_jobcontrol.myenv;
	while (envp[i])
	{
		tmp = ft_strsplit(envp[i], '=');
		save->keyval = ft_strdup(envp[i]);
		save->key = ft_strdup(tmp[0]);
		save->val = ft_strdup(tmp[1]);
		if (envp[i + 1])
		{
			save->next = ft_memalloc(sizeof(*g_jobcontrol.myenv));
			save = save->next;
		}
		ft_freetab(tmp);
		i++;
	}
	save = NULL;
}

void		init_myloc(char **envp)
{
	int		i;
	t_myloc	*save;
	char	**tmp;

	i = 0;
	g_jobcontrol.myloc = ft_memalloc(sizeof(*g_jobcontrol.myloc));
	g_jobcontrol.myloc->next = NULL;
	save = g_jobcontrol.myloc;
	while (envp[i])
	{
		tmp = ft_strsplit(envp[i], '=');
		save->keyval = ft_strdup(envp[i]);
		save->key = ft_strdup(tmp[0]);
		save->val = ft_strdup(tmp[1]);
		if (envp[i + 1])
		{
			save->next = ft_memalloc(sizeof(*g_jobcontrol.myloc));
			save = save->next;
		}
		ft_freetab(tmp);
		i++;
	}
	save = NULL;
}

void		init_jc(char **envp)
{
	init_myenv(envp);
	init_myloc(envp);
	g_jobcontrol.env = 0;
	g_jobcontrol.f = 0;
	g_jobcontrol.stdi = -1;
	g_jobcontrol.stde = -1;
	g_jobcontrol.stdo = -1;
	g_jobcontrol.ass = NULL;
	g_jobcontrol.mypath = NULL;
	g_jobcontrol.ass_stock = NULL;
	g_jobcontrol.first_job = NULL;
	g_jobcontrol.alias = NULL;
}
