/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 23:38:57 by mabayle           #+#    #+#             */
/*   Updated: 2020/04/22 16:21:42 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/projectinclude.h"

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
	else if (((*s).env = init_lst_env(NULL, envp, NULL, 0)) == NULL)
		ft_exit(0, &*s);
	envp = save;
	init_start_pwd(s);
	if (((*s).env_path = search_pathenv((*s).env)) == NULL)
		ft_eputstr("42sh "MAGENTA"warning"
		WHITE": the PATH environment variable does not exist.\n\0");
}

int			main(int ac, char **av, char **envp)
{
	init_shell_sig();
	init_jc(envp);
	init_struct(&g_jobcontrol.s, envp);
	g_shell = init_shell(0);
	g_jobcontrol.s.h = create_history(NULL, NULL, NULL, &g_jobcontrol.s);
	ac == 2 && ft_strcmp(av[1], "DEBUG") == 0 ? g_shell->debug = 1 : 0;
	while (init_lst(&g_jobcontrol.s, 0, 2, 0))
	{
		if (g_jobcontrol.s.cmd)
		{
			g_shell->line = g_jobcontrol.s.cmd;
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
