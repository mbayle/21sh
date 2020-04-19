/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 23:38:57 by mabayle           #+#    #+#             */
/*   Updated: 2020/04/17 13:12:13 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/projectinclude.h"

t_21sh	*init_shell(int debug)
{
	t_21sh		*shell;

	shell = ft_memalloc(sizeof(*shell));
	shell->lex = NULL;
	shell->lex_size = 0;
	shell->ast = NULL;
	shell->debug = debug;
	return (shell);
}

static void	init_term(t_struct *s)
{
//	int		ret;

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

static void	init_start_pwd(t_struct *s)
{
	t_lst2	*env;

	env = s->env;
	while (env && ft_strcmp(env->varn, "PWD"))
		env = env->next;
	if (env)
		s->start_pwd = ft_strdup(env->var);
	else
		s->start_pwd = NULL;
	g_lined = s;
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
	else
		if (((*s).env = init_lst_env(NULL, envp, NULL, 0)) == NULL)
			ft_exit(0, &*s);
	envp = save;
	init_start_pwd(s);
	if (((*s).env_path = search_pathenv((*s).env)) == NULL)
		ft_eputstr("Shell "MAGENTA"warning"
		WHITE": the PATH environment variable does not exist.\n\0");
}

void		tmp_free_struct(t_struct *s)
{
	t_lst	*del;

	while ((del = (*s).lbg))
	{
		(*s).lbg = (*s).lbg->next;
		free(del);
	}
	(*s).l = NULL;
	(*s).lbg = NULL;
	(*s).tmp = NULL;
	free_dchar(&(*s).envi);
	(*s).av = NULL;
}

char		**ft_tabdup(char **av)
{
	int 	i;
	char	**dst;

	i = 0;
	while (av[i])
		i++;
	if (!(dst = malloc(sizeof(char*) * (i + 1))))
		return (NULL);
	i = -1;
	while (av[++i])
		dst[i] = ft_strdup(av[i]);
	dst[i] = NULL;
	return (dst);
}

void		init_myenv(char	**envp)
{
	int		i;
	t_myenv	*save;
	char	**tmp;

	i = 0;
	g_jobcontrol.myenv = ft_memalloc(sizeof(*g_jobcontrol.myenv));
	g_jobcontrol.myenv->next = NULL;
	save = g_jobcontrol.myenv;;
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

void		init_myloc(char	**envp)
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
//	g_jobcontrol.heredoc = ft_strnew(1);
	g_jobcontrol.f = 0;
	g_jobcontrol.stdi = -1;
	g_jobcontrol.stde = -1;
	g_jobcontrol.stdo = -1;
	g_jobcontrol.ass = NULL;
	g_jobcontrol.mypath = NULL;
	g_jobcontrol.ass_stock = NULL;
//	ft_bzero(&g_jobcontrol, sizeof(g_jobcontrol));
	g_jobcontrol.first_job = NULL;
	g_jobcontrol.alias = NULL;
}

int			main(int ac, char **av, char **envp)
{
//	int			c;

//	c = 0;

	init_shell_sig();
	init_jc(envp);
//	g_jobcontrol.env = ft_tabdup(envp);
	init_struct(&g_jobcontrol.s, envp);
	g_shell = init_shell(0);
	g_jobcontrol.s.h = create_history(NULL, NULL, NULL, &g_jobcontrol.s);
	ac == 2 && ft_strcmp(av[1], "DEBUG") == 0 ? g_shell->debug = 1 : 0;
	while (init_lst(&g_jobcontrol.s, 0, 2, 0))
	{
		if (g_jobcontrol.s.cmd)
		{
//			update_bg_status();
			g_shell->line = g_jobcontrol.s.cmd;
//			ft_putendl("-----");
//			ft_putendl(g_shell->line);
//			ft_putendl("-----");
			update_bg_status();
			g_shell->line = g_jobcontrol.s.cmd;
			ft_lexer(&g_shell->lex, g_shell->line);
		}
		fill_struct_env();
		tmp_free_struct(&g_jobcontrol.s);
		update_bg_status();
		if (isatty(0) == 0)
			break ;
	}
	reset_attr();
	delete_job(g_jobcontrol.first_mail);
	return (0);
}
