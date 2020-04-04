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
		dest[c] = ft_mstrcpy(NULL, src[c]);
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
	t_lst2          *l;
	char            *tmp;

	l = (*s).env;
	while (l && (ft_strncmp(l->env, "HOME", 4) != 0))
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
		if ((new = mini_strjoin(l->env, tmp)) == NULL)
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
	tmp = (*s).av[1];
	g_jobcontrol.s.i = 1;
	if ((cwd = getcwd(cwd, PATH_MAX)) == NULL)
		return (0);
	if (((*s).av[1] = ft_strjoin("PWD=", cwd)) == NULL)
		return (0);
	if (tmp)
		free(tmp);
	if (cwd)
		free(cwd);
	if (exec_setenv_b(&*s, s->av, 1, 1))
		return (0);
	free((*s).av[1]);
	if (((*s).av[1] = ft_strjoin("OLDPWD=", ocwd)) == NULL)
		return (0);
	if (exec_setenv_b(&*s, s->av, 1, 1))
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
	if ((new[0] = ft_mstrcpy(new[0], *av[0])) == NULL)
		return (0);
	free_dchar(&*av);
	new[1] = NULL;
	new[2] = NULL;
	return (new);
}

int			exec_cd_ex(t_struct *s, char **tmp, char **ocwd)
{
	t_lst2	*env;

	*ocwd = getcwd(*ocwd, PATH_MAX);
	env = s->env;
	check_ls(s);
	if (ft_strcmp((*s).av[1], "-") == 0)
	{
		while (env && (ft_strcmp(env->varn, "OLDPWD")) != 0)
			env = env->next;
		if (env)
		{
			free((*s).av[1]);
			if (((*s).av[1] = ft_mstrcpy((*s).av[1], env->var)) == NULL)
			{
				*tmp = s->av[1];
				return (0);
			}
		}
		else
			ft_eputendl(MAGENTA"Warning"WHITE": OLDPWD var. doesn't exist.");
	}
	*tmp = s->av[1];
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

	exec_cd_ex(s, &tmp, &ocwd);
	if (!(*s).av[1])
	{
		if (((*s).av = modif_av(&(*s).av)) == NULL)
			return (0);
		while (tp && ft_strcmp(tp->varn, "HOME"))
			tp = tp->next;
		if (!tp)
		{
			tmp = NULL;
			ft_eputstr("minishell: "MAGENTA"warning"
					WHITE": the HOME environment variable does not exist.\n\0");
		}
		else
			tmp = tp->var;
	}
	if ((r = chdir(tmp)) == -1)
	{
		//ft_eputstr("System chdir call failed.\n");
		;
	}
	else
		if (exec_cd2(&*s, NULL, ocwd, NULL) == 0)
			return (0);
	if (r == -1)
	{
		fp("mb", NULL);
		ft_putstr(RED);
		ft_2eputstr(ocwd, " -X ");
		ft_eputendl(s->av[1]);
	}
	else
	{
		ft_putstr(GREEN);
		ft_2putstr(ocwd, "  ➜  ");
		ft_putendl(tmp);
	}
	ft_putstr(WHITE);
	free_dchar(&s->av);
	return (1);
}
