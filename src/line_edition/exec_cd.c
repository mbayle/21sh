/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 22:55:09 by frameton          #+#    #+#             */
/*   Updated: 2020/03/10 18:48:45 by frameton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

char	**cpy_tab(char **src)
{
	int		c;
	char	**dest;

	c = 0;
	while (src[c])
		++c;
	dest = (char**)malloc(sizeof(*dest) * (c + 1));
	c = 0;
	while (src[c])
	{
		dest[c] = ft_strdup(src[c]);
		++c;
	}
	dest[c] = NULL;
	return (dest);
}


char    *mini_strjoin(char *s1, char *s2)
{
	char    *dest;
	char    *sa;

	sa = NULL;
	while (*s1 && *s1 != '=')
		s1++;
	s1++;
	if (s1 && s2)
	{
		if ((dest = ft_strnew((ft_strlen((char *)s1) + ft_strlen((char *)s2))))
				== NULL)
			return (NULL);
		sa = dest;
		dest = ft_strcpy(dest, s1);
		dest = ft_pstrback(dest);
		dest++;
		dest = ft_strcpy(dest, s2);
	}
	return (sa);
}

int             create_path_home(t_struct *s, char *new, int i)
{
	t_myenv         *l;
	char            *tmp;

	l = g_jobcontrol.myenv;
	while (l && (ft_strncmp(l->keyval, "HOME", 4) != 0))
		l = l->next;
	if (!l)
	{
		ft_eputstr(MAGENTA"warning"WHITE": the home variable doesn't exist.\n");
		return (0);
	}
	else
	{
		tmp = (*s).av[i];
		tmp++;
		if ((new = mini_strjoin(l->keyval, tmp)) == NULL)
			return (-1);
		tmp--;
		free_char(&tmp);
		(*s).av[i] = new;
	}
	return (1);
}

int             exec_cd2(t_struct *s, char *cwd, char *ocwd, char *tmp)
{
	(*s).prompt = 0;
//	if ((*s).av[1])
//		tmp = ft_strdup((*s).av[1]);
	g_jobcontrol.s.i = 1;
	ft_putendl((*s).av[1]);
	if (g_jobcontrol.p == 0) //&& (*s).av[1])
	{
		if (!(cwd = ft_strdup(g_jobcontrol.mypath)))
			cwd = getcwd(NULL, 0);
	}
	else
	{
		ft_strdel(&(*s).av[2]);
		if (g_jobcontrol.p == 1 && (cwd = getcwd(cwd, PATH_MAX)) == NULL)
			return (0);
		else
			cwd = ft_strdup(g_jobcontrol.mypath);
	}
	free((*s).av[1]);
	if (((*s).av[1] = ft_strjoin("PWD=", cwd)) == NULL)
		return (0);
	if (tmp)
		ft_strdel(&tmp);
	if (cwd)
		free(cwd);
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

char    **modif_av(char ***av)
{
	char    **new;

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

int			exec_cd_ex(t_struct *s, char **tmp, char **ocwd)
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
	/*if ((*s).av[i][0] && (*s).av[i][0] == '~')
		if ((c = create_path_home(&*s, NULL, i)) < 1)
		{
			if (c == 0)
				return (1);
			if (c == -1)
				return (0);
		}*/
}

int             exec_cd(t_struct *s, t_lst2 *tp, char *tmp, char *ocwd)
{
	int		r;

	r = -1;
	if (exec_cd_ex(s, &tmp, &ocwd) == -1)
	{
		ft_strdel(&ocwd);
		ft_freetab(s->av);
		return (0);
	}
	if (!(*s).av[1])
	{
//		printf("%p\n", s->av);
		if (((*s).av = modif_av(&(*s).av)) == NULL)
		{
			ft_putendl("IN TH");
			ft_strdel(&ocwd);
			ft_freetab(s->av);
			ft_strdel(&tmp);
			return (0);
		}
//		printf("%p\n", s->av);
		while (tp && ft_strcmp(tp->varn, "HOME"))
			tp = tp->next;
		if (!tp)
		{
			ft_strdel(&tmp);
			tmp = NULL;
			ft_eputstr("minishell: "MAGENTA"warning"
					WHITE": the HOME environment variable does not exist.\n\0");
		}
		else
			tmp = ft_strdup(tp->var);
	}
	ft_putendl(tmp);
	if (tmp && (r = chdir(tmp)) == -1)
	{
		//ft_eputstr("System chdir call failed.\n");
		;
	}
	else
	{
		if (exec_cd2(&*s, NULL, ocwd, NULL) == 0)
		{
			ft_strdel(&ocwd);
			ft_freetab(s->av);
			ft_strdel(&tmp);
			ft_putendl("WHY HE");
			return (0);
		}
	}
	if (r == -1)
	{
	//	fp("mb", NULL);
		ft_putstr(RED);
		ft_2eputstr(ocwd, " -X ");
		ft_eputendl(tmp);
	}
	else
	{
		ft_putstr(GREEN);
		ft_2putstr(ocwd, "  ➜  ");
		ft_putendl(tmp);
	}
	ft_putstr(WHITE);
//	printf("%p\n", ocwd);
	ft_freetab(s->av);
//	s->av = NULL;
	ft_strdel(&ocwd);
//	ocwd = NULL;
//	free_dchar(&s->av);
	ft_strdel(&tmp);
//	printf("%p\n", tmp);
//	printf("%p\n", s->av);
	return (1);
}
