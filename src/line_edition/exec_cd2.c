/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 23:01:08 by frameton          #+#    #+#             */
/*   Updated: 2020/03/10 02:52:38 by frameton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

int		exec_cd2b(t_struct *s, char *ocwd)
{
	if (mysetenv(s->av, 1))
		return (0);
	free((*s).av[1]);
	if (((*s).av[1] = ft_strjoin("OLDPWD=", ocwd)) == NULL)
		return (0);
	if (mysetenv(s->av, 1))
		return (0);
	g_jobcontrol.s.i = 0;
	return (1);
}

char	**modif_av(char ***av)
{
	char	**new;

	new = NULL;
	if ((new = (char**)malloc(sizeof(*new) * 3)) == NULL)
		return (0);
	if ((new[0] = ft_strdup(*av[0])) == NULL)
	{
		free_dchar(&*av);
		*av = NULL;
		ft_memdel((void**)&new);
		return (0);
	}
	ft_freetab(*av);
	*av = NULL;
	new[1] = NULL;
	new[2] = NULL;
	return (new);
}

int		exec_cd_ex(t_struct *s, char **tmp, char **ocwd)
{
	t_myenv	*env;

	*ocwd = getcwd(*ocwd, PATH_MAX);
	env = g_jobcontrol.myenv;
	if (check_ls(s) == -1)
		return (-1);
	if (ft_strcmp((*s).av[1], "-") == 0)
	{
		while (env && (ft_strcmp(env->key, "OLDPWD")) != 0)
			env = env->next;
		if (env)
		{
			ft_strdel(&(*s).av[1]);
			if (((*s).av[1] = ft_strdup(env->val)) == NULL)
			{
				*tmp = ft_strdup(s->av[1]);
				return (0);
			}
		}
		else
			ft_eputendl(MAGENTA"Warning"WHITE": OLDPWD var. doesn't exist.");
	}
	if (s->av && s->av[0] && s->av[1])
		*tmp = ft_strdup(s->av[1]);
	return (0);
}

int		exec_cd_n(t_struct *s, char **ocwd, t_lst2 **tp, char **tmp)
{
	if (((*s).av = modif_av(&(*s).av)) == NULL)
	{
		ft_putendl("IN TH");
		ft_strdel(ocwd);
		ft_freetab(s->av);
		ft_strdel(tmp);
		return (1);
	}
	while (*tp && ft_strcmp((*tp)->varn, "HOME"))
		*tp = (*tp)->next;
	if (!*tp)
	{
		ft_strdel(tmp);
		*tmp = NULL;
		ft_eputstr("minishell: "MAGENTA"warning"
				WHITE": the HOME environment variable does not exist.\n\0");
	}
	else
		*tmp = ft_strdup((*tp)->var);
	return (0);
}

int		exec_cd_n2(int r, char **ocwd, char **tmp, t_struct *s)
{
	if (r == -1)
	{
		ft_putstr(RED);
		ft_2eputstr(*ocwd, " -X ");
		ft_eputendl(*tmp);
	}
	else
	{
		ft_putstr(GREEN);
		ft_2putstr(*ocwd, "  ➜  ");
		ft_putendl(*tmp);
	}
	ft_putstr(WHITE);
	ft_freetab(s->av);
	ft_strdel(ocwd);
	ft_strdel(tmp);
	return (0);
}
