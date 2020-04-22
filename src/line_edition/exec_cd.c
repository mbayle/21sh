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

#include "../../includes/projectinclude.h"

char		**cpy_tab(char **src)
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


char		*mini_strjoin(char *s1, char *s2)
{
	char	*dest;
	char	*sa;

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

int			create_path_home(t_struct *s, char *new, int i)
{
	t_myenv		*l;
	char		*tmp;

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

int			exec_cd2(t_struct *s, char *cwd, char *ocwd, char *tmp)
{
	(*s).prompt = 0;
	g_jobcontrol.s.i = 1;
	if (g_jobcontrol.p == 0)
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
	return (exec_cd2b(s, ocwd));
}

int			exec_cd(t_struct *s, t_lst2 *tp, char *tmp, char *ocwd)
{
	int		r;

	r = -1;
	if (exec_cd_ex(s, &tmp, &ocwd) == -1)
	{
		ft_strdel(&ocwd);
		ft_freetab(s->av);
		return (1);
	}
	if (!(*s).av[1])
		if (exec_cd_n(s, &ocwd, &tp, &tmp))
			return (1);
	if (tmp && (r = chdir(tmp)) == -1)
		;
	else
	{
		if (exec_cd2(&*s, NULL, ocwd, NULL) == 0)
		{
			ft_strdel(&ocwd);
			ft_freetab(s->av);
			ft_strdel(&tmp);
			return (1);
		}
	}
	return (exec_cd_n2(r, &ocwd, &tmp, s));
}
