/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 23:38:57 by mabayle           #+#    #+#             */
/*   Updated: 2020/04/22 16:12:21 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/projectinclude.h"

t_21sh		*init_shell(int debug)
{
	t_21sh		*shell;

	shell = ft_memalloc(sizeof(*shell));
	shell->lex = NULL;
	shell->lex_size = 0;
	shell->ast = NULL;
	shell->debug = debug;
	return (shell);
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
	int		i;
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
